#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "TableErrorHandle.c"

#define ERROR_CODE (-1)

/**
 * @brief clone an int
 */
void* cloneInt(const void* i)
{
    assert(i != NULL);
    void *temp = malloc(sizeof(int));
    if(temp == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    *((int*)temp) = *((int*) i);
    return temp;
}

/**
 * @brief free an int
 */
void freeInt( void* i)
{
    assert(i != NULL);
    free(i);
}


/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to an int
 * @return number between 0-(tableSize-1)

 */
int intFcn (const void* key, size_t tableSize)
{
    assert(key != NULL && tableSize > 0);
    return (* (int*) key) % (int) tableSize;
}

/**
 * @brief print a string
 *  assuming key pointer to an int
 *
 */
void intPrint (const void* key){
    assert(key == NULL);
    printf("%d", *(int*) key);
}
/**
 *  intCompare - pointer to int comparison function:
 * @brief compare 2 ints
 *   returns zero int if both ints are equal, otherwise
 *   returns non-zero.
 *
 */
int intCompare (void *key1, void *key2){
    assert(key1 != NULL && key2 != NULL);
    int *val1 = (int*) key1, *val2 = (int*) key2;
    return *val1 - *val2;
}
