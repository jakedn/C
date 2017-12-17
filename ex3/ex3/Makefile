CC= gcc
CFLAGS= -c -Wvla -Wall -Wextra -std=c99 -DNDEBUG
CODEFILES= ex3.tar Makefile MyIntFunctions.c MyStringFunctions.c MyIntFunctions.h MyStringFunctions.h GenericHashTable.c Key.h
LIBFILES= GenericHashTable.o TableErrorHandle.o Key.h

# All Target
all: HashIntSearch
	./HashIntSearch 1 0

# Exceutables
GenericHashTable: libgenericHashTable.a

libgenericHashTable.a: $(LIBFILES)
	ar rcs libgenericHashTable.a $(LIBFILES)

HashStrSearch: HashStrSearch.o libgenericHashTable.a MyStringFunctions.o
	$(CC) MyStringFunctions.o HashStrSearch.o -L. libgenericHashTable.a -o HashStrSearch

HashIntSearch: HashIntSearch.o libgenericHashTable.a MyIntFunctions.o
	$(CC) MyIntFunctions.o HashIntSearch.o -L. libgenericHashTable.a -o HashIntSearch

# Object Files
GenericHashTable.o: GenericHashTable.c GenericHashTable.h TableErrorHandle.h
	$(CC) $(CFLAGS) GenericHashTable.c -o GenericHashTable.o

MyIntFunctions.o: MyIntFunctions.c MyIntFunctions.h TableErrorHandle.h Key.h
	$(CC) $(CFLAGS) MyIntFunctions.c -o MyIntFunctions.o

MyStringFunctions.o: MyStringFunctions.c MyStringFunctions.h TableErrorHandle.h
	$(CC) $(CFLAGS) MyStringFunctions.c -o MyStringFunctions.o

HashIntSearch.o: HashIntSearch.c GenericHashTable.h MyIntFunctions.h
	$(CC) $(CFLAGS) HashIntSearch.c -o HashIntSearch.o

HashStrSearch.o: HashStrSearch.c MyStringFunctions.h GenericHashTable.h
	$(CC) $(CFLAGS) HashStrSearch.c -o HashStrSearch.o

TableErrorHandle.o: TableErrorHandle.c TableErrorHandle.h
	$(CC) $(CFLAGS) TableErrorHandle.c -o TableErrorHandle.o


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -f *.o HashIntSearch HashStrSearch GenericHashTable.a *.tar

# Things that aren't really build targets
.PHONY: clean tar 
