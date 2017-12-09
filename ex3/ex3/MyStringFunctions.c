#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TableErrorHandle.h"
#include <assert.h>

#define EQUAL 0
#define NEQUAL 1
#define ERROR_CODE (-1)

//TODO asserts in all functionss
/**
 * @brief clone a string
 */
void* cloneStr(const void*  s)
{
    assert(s != NULL);
    char *temp = (char *) s;
    size_t length = strlen(temp);
    assert(length > 0);
    void *news = malloc((length + 1) * sizeof(char));
    if(news == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    for(size_t i = 0; i < (length + 1) * sizeof(char); i++)
    {
        news[i] = s[i];
    }
    return news;
}

/**
 * @brief free an string
 */
void freeStr(void* s)
{
    free(s);
}


/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to string
 * @return number between 0-(tableSize-1)

 */
int strFcn (const void*  s, size_t tableSize)
{
    if(s == NULL || tableSize <= 0)
    {
        return ERROR_CODE;
    }
    char *temp = (char *) s;
    int sum = 0, size = (int) tableSize;
    size_t length = strlen(temp);
    if(length == 0)
    {
        return ERROR_CODE;
    }
    for(int i = 0; i < length; i++)
    {
        sum += temp[i];
    }
    return sum % size;
}

/**
 * @brief print a string
 *  assuming key pointer to string
 *
 */
void strPrint (const void*  s)
{
    char *temp = (char *) s;
    printf("%s", temp);
}

/**
 *  strCompare - pointer to int comparison function:
 * @brief compare 2 strings
 *   returns zero int if both strings are equal, otherwise
 *   returns non-zero.
 */
int strCompare (const void *s1, const void *s2)
{
    assert(s1 != NULL && s2 != NULL);
    char *temp1 = (char *) s1;
    char *temp2 = (char *) s2;
    if(strcmp(temp1, temp2) == EQUAL)
    {
        return EQUAL;
    }
    return NEQUAL;
}
