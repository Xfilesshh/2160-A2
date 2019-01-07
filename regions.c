
//#-----------------------------------------
//#NAME: Natasha Wagner
//#STUDENT NUMBER: 7747861
//#COURSE: COMP 2160, SECTION A01
//#INSTRUCTOR: FRANKLIN BRISTOW
//#ASSIGNMENT: Assignment 4, Question 1
//#
//#REMARKS: This program stores blocks inside regions. It is able to eliminate the blocks or the regions and  print the info as needed.
//#-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "regions.h"

struct BLOCK{
    unsigned * next;       //the next block
    r_size_t bSize;        //the size of the block
};
typedef struct BLOCK Block;

struct REGION{
    const char * rName;      //region name
    r_size_t rSize;          //region size
    Block * blockTop;        //the first block in the region
    unsigned * next;         //the next region
    r_size_t sizeLeft;       //the size left in the region
};
typedef struct REGION Region;

//Structs

Boolean rinit(const char *region_name, r_size_t region_size);
Boolean rchoose(const char *region_name);
const char *rchosen();
void *ralloc(r_size_t block_size);
r_size_t rsize(void *block_ptr);
Boolean rfree(void *block_ptr);
void rdestroy(const char *region_name);
void rdump();
r_size_t roundUp(r_size_t block_size);

//initializing methods

static Region * head = NULL;      //the first region
static Region * current = NULL;   //the current region

//rinit
    //
    //PURPOSE: This method initializes regions. It creates the space for them to be placed.
    //INPUT PARAMETERS: This function has the const char *region_name, r_size_t region_size as parameters. Region_name and region_size are
    //both used to create the new region.
    //OUTPUT PARAMETERS: This function returns the Boolean result of rChoose which indicates whether or not the new Region was selected
    //as the current region.
    //
    //rinit

Boolean rinit(const char *region_name, r_size_t region_size){

    Boolean result = false;
    Region * newRegion = NULL;
    Region * temp = head;
    region_size = roundUp(region_size);
    
    if(region_size != 0 && !(rchoose( region_name ))){
    
        if(head == NULL){
            head =(Region*) malloc( region_size );       //initialize head (first) region
            head->rName = region_name;
            head->rSize = region_size;
            head->next = NULL;
            head->blockTop = NULL;
            head->sizeLeft = region_size;
            result = rchoose( head->rName );
        }//if
      
           else{
           
              newRegion =(Region*) malloc( region_size );
                  
              newRegion->rName = region_name;                   //initialize other regions
              newRegion->rSize = region_size;
              newRegion->next = NULL;
              newRegion->blockTop = NULL;
              newRegion->sizeLeft = region_size;
              
                while(temp != NULL){
                
                  if(temp->next == NULL && !result)
                    temp->next = (unsigned *) newRegion;
                  
                  else
                    temp = (Region *) temp->next;
                  
              }//while
              
            result = rchoose( newRegion->rName );
           
           }//else

    }//if
 
  return result;
}//rinit

//rchoose
    //
    //PURPOSE: This method selects the indicated region to be the current region.
    //INPUT PARAMETERS: This function has const char * region_name as input parameters. It is used to find the region with the matching name.
    //OUTPUT PARAMETERS: This function returns the Boolean result of whether it was able to find and set the wanted region as the current region.
    //
    //rchoose
    
Boolean rchoose(const char *region_name){

  Region * current1 = head;     //pointer to the first region
  Boolean result = false;       //boolean result of whether it was set or not

  while(current1 != NULL && !result){

    if(current1->rName != region_name){ 
     
        if(current1->next == NULL)
           current1 = NULL;
        
        else
           current1 = (Region *)current1->next;
          
    }//if
    
    else{
        current = current1;
        result = true;
    }//else
    
  }//while

  return result;
}//rchoose

//rchosen
    //
    //PURPOSE: This method returns the name of the currently selected region.
    //INPUT PARAMETERS: This function has no input parameters.
    //OUTPUT PARAMETERS: This function returns the const char * of the current region.
    //
    //rchosen
const char *rchosen(){
  return current->rName;        
}

//ralloc
    //
    //PURPOSE: This method creates a block of the indicated size in the next available position.
    //INPUT PARAMETERS: This function has r_size_t block_size as input parameters. It is used to create a block of the wanted size.
    //OUTPUT PARAMETERS: This function returns a pointer of the location of the block or null it is failed to create it as output parameters.
    //
    //ralloc
    
void *ralloc(r_size_t block_size){

    Block * location = NULL;                //location of the new block
    Block * temp = current->blockTop;       //the first block in the selected region
    Boolean result = false;                 //true or false of whether it was successfully inserted (for loop)
    block_size = roundUp(block_size);       //the rounded up value of the block size
   

    if(block_size != 0 && current != NULL){

      if(block_size <= current->sizeLeft){
      
        location =(Block *) malloc(block_size);
        
        if(temp == NULL && location != NULL){
                                                                    //insert for if there were no blocks in the region
          current->blockTop = (Block *) location;
          ((Block *) current->blockTop)->next = NULL;
          ((Block *) current->blockTop)->bSize = block_size;
          current->sizeLeft =  (current->sizeLeft) - block_size;
        }//if
        
        else{
         
            while(temp != NULL && !result && location != NULL){            //shifts through blocks to find an empty spot
                                                                           //to insert it in
                  if((Block *)temp->next == NULL){
                  
                      temp->next = (unsigned *) location;
                      ((Block *) temp->next)->next = NULL;
                      location->bSize = block_size;
                      current->sizeLeft =  (current->sizeLeft) - block_size;
                      result = true;
                      temp = (Block *) temp->next;
                   }//if
                  
                  else{
                  
                    if(temp->next != NULL)
                       temp = (Block *) temp->next;
                     
                  }//else
            }//while
        }//else
     }//if
  }//if
  return location;
}//ralloc

//rsize
    //
    //PURPOSE: This method returns the size of the indicated block pointer in the current region. 
    //INPUT PARAMETERS: This function has void *block_ptr as input parameters. It is the pointer to the block.
    //OUTPUT PARAMETERS: This function returns the r_size_t of the size of the block as output parameters.
    //
    //rsize
r_size_t rsize(void *block_ptr){
   return ((Block *)block_ptr)->bSize;
}//rsize

//rfree
    //
    //PURPOSE: This method frees the space used by the given pointer in the current region. 
    //INPUT PARAMETERS: This function has void *block_ptr as input parameters. It is the pointer to the block.
    //OUTPUT PARAMETERS: This function returns the boolean result as a true or false to if the block was freed as output parameters.
    //
    //rfree
Boolean rfree(void *block_ptr){

    Block * temp = (Block *)current->blockTop;       //top block of the region
    Boolean found = false;                           //boolean to if it was freed
    
    if(block_ptr != NULL){
    
        while(temp != NULL && !found){
        
          if((Block *)temp->next == (Block *) block_ptr){
              block_ptr = (Block *)temp->next;                      
              temp->next = ((Block * )temp->next)->next;
              current->sizeLeft = (current->sizeLeft + ((Block *) block_ptr)->bSize);
               
              free(block_ptr);
              found = true;
          }//if
          
          else
              temp = (Block *) temp->next;
            
        }//while
    
    }//if
 
    return found;
}//rfree

//rdestroy
    //
    //PURPOSE: This method deleted the given region and its memory. 
    //INPUT PARAMETERS: This function has const char *region_name as input parameters. It is the pointer to the region to be deleted.
    //OUTPUT PARAMETERS: This function has no output parameters.
    //
    //rdestroy
    
void rdestroy(const char *region_name){

    Region * current1 = head;         //first region (for loop)
    unsigned * temp = NULL;           //to save the region to be deleted while changing its next pointers
    Boolean found = false;            //boolean for finding it in for loop

    while(current1 != NULL && !found){
    
      if(current1->rName ==region_name){
                                             //delete region if FIRST region
        head = (Region *) current1->next;
        free(current1);
      }//if
    
      else{
        
        if(((Region *) current1->next)->rName == region_name){             //delete region
            
          temp = current1->next;
            
              if(((Region *) current1->next) ->next != NULL)
              current1->next = ((Region *) current1->next) ->next;
            
              else
                current1->next = NULL;
            
          free(temp);
        }//if
        
        else
          current1 = (Region *)current1->next;
        
      }//else
  }//while   
}//rdestroy

//rdump
    //
    //PURPOSE: This method prints out the results. 
    //INPUT PARAMETERS: This function has no input parameters.
    //OUTPUT PARAMETERS: This function prints out the results to the user.
    //
    //rdump
    
void rdump(){

  Region * region1 = head;                     //first region (for looping)
  Block * block2 = (Block *) region1->blockTop;   //first block (for looping)
  r_size_t total = 0;                             //the total size used
  
  while(region1 != NULL){
      printf("\nRegion: %s\n", region1->rName);
       
      if(block2 != NULL){
        printf("\nBlocks: \n");
        
        while(block2 != NULL){
        
            printf("--- %p, size: %hu\n", block2, block2->bSize);
            total = total + (block2->bSize);
            block2 = (Block *) block2->next;
        }//while
      }//if
      else
        printf("There are no blocks.");
      
      printf("\nTotal size left: %d\n", (total/(region1->rSize)));
      total = 0;
      region1 =(Region *) region1->next;
  }//while
}//rdump
  //rdump
    //
    //PURPOSE: This method rounds up the size to the closest multiple of 8. 
    //INPUT PARAMETERS: This function has r_size_t block_size as input parameters which is for converting it.
    //OUTPUT PARAMETERS: This function returns the result of the conversion.
    //
    //rdump
r_size_t roundUp(r_size_t block_size){
  return (((block_size + 4) / 8) * 8);
}//roundUp