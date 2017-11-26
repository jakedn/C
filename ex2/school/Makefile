CC= gcc
CFLAGS= -c -Wvla -Wall -Wextra -std=c99
CODEFILES= ex2.tar MyString.c BuggyLinkedList.c Makefile


# All Target
all: MyString

# Exceutables
MyString: MyString.o
	ar rcs MyString.a 

BuggyLinkedList: BuggyLinkedList.o
	$(CC) BuggyLinkedList.o -o BuggyLinkedList
	./BuggyLinkedList 

# Object Files

MyString.o: MyString.c MyString.h
	$(CC) $(CFLAGS) MyString.c -o MyString.o

BuggyLinkedList.o: BuggyLinkedList.c
	$(CC) $(CFLAGS) BuggyLinkedList.c -o BuggyLinkedList.o


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -f *.o BuggyLinkedList MyString.a

# Things that aren't really build targets
.PHONY: clean tar 
