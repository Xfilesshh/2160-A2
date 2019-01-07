
#-----------------------------------------
#NAME: Natasha Wagner
#STUDENT NUMBER: 7747861
#COURSE: COMP 2160, SECTION A01
#INSTRUCTOR: FRANKLIN BRISTOW
#ASSIGNMENT: Assignment 4, Question 1
#
#REMARKS: This program stores blocks inside regions. It is able to eliminate them as needed.
#-----------------------------------------

CC = clang
CFLAGS = -g -Wall

PROG = main

OBJDIR = objects
OBJS = $(OBJDIR)/main.o $(OBJDIR)/regions.o

# ... and in the darkness bind them (er, link them)
$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

# One rule to build them all...
$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# $@ is a variable with the name of the file that caused the rule
# to run. We've got multiple .c files, and thus multiple .o files,
# so each one of the .c files will create a separate .o file.
# $< is the name of the first prerequisite (in this case the .c)
# file. So our recipe will expand to something like:
# 	$(CC) $(CFLAGS) -c -o myfile.o myfile.c

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(PROG)
#-----------------------------------------
#NAME: Natasha Wagner
#STUDENT NUMBER: 7747861
#COURSE: COMP 2160, SECTION A01
#INSTRUCTOR: FRANKLIN BRISTOW
#ASSIGNMENT: Assignment 4, Question 1
#
#REMARKS: This program takes words and inserts into a table and error checks.
#-----------------------------------------

CC = clang
CFLAGS = -g -Wall

PROG = main

OBJDIR = objects
OBJS = $(OBJDIR)/main.o $(OBJDIR)/regions.o

# ... and in the darkness bind them (er, link them)
$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

# One rule to build them all...
$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# $@ is a variable with the name of the file that caused the rule
# to run. We've got multiple .c files, and thus multiple .o files,
# so each one of the .c files will create a separate .o file.
# $< is the name of the first prerequisite (in this case the .c)
# file. So our recipe will expand to something like:
# 	$(CC) $(CFLAGS) -c -o myfile.o myfile.c

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(PROG)
