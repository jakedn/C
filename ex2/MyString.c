#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"

#define ERROR_CODE -2

/**
 * this struct represents a string
 */
struct MyString
{
    char *str;
};

/**
 * allocates a new String containing the str1 char*
 * @param str1 a char*
 * @return a new MyString * struct contaning str1
 */
MyStringP createStringFromChars(const char* str1)
{
    if(str1 == NULL)
    {
        return NULL;
    }
    MyStringP newString = (MyStringP) malloc(sizeof(struct MyString));
    unsigned int length = 0;
    unsigned int i = 0;
    while(str1[i] != '\0')
    {
        length++;
        i++;
    }
    length++;   //allocating for the '\0' char at the end
    newString->str = (char *) malloc(length * sizeof(char));

    //this loop now makes newString->str identical to str1
    for(i = 0; i < length; i++)
    {
        newString->str[i] = str1[i];
    }
    return newString;
}


/**
 * allocates a new String which is a copy of str1
 * @param str1 a String
 * @return a copy of str1
 */
MyStringP createStringFromString(const MyStringP str1)
{
    if(str1 == NULL)
    {
        return NULL;
    }
    MyStringP newString = (MyStringP) malloc(sizeof(struct MyString));
    newString->str = (char *) malloc((lengthString(str1) + 1) * sizeof(char));
    // we make newString->str equal '' so that we can use a the defined function
    // concatString
    newString->str[0] = '\0';
    concatString(newString, str1);
    return newString;
}


/**
 * frees the allocated memory given to the struct
 * @param str1 the string to free
 */
void freeString(MyStringP str1)
{
    if(str1->str != NULL)
    {
        free(str1->str);
    }
    free(str1);
}


/**
 * returns the lenght of the given String
 * @param str1 - the string
 * @return lenght of str1
 */
unsigned int lengthString(const MyStringP str1)
{
    if(str1 == NULL)
    {
        return (unsigned int) ERROR_CODE;
    }
    unsigned int length = 0;
    char *p = str1->str;
    while(*p != '\0')
    {
        length++;
        p++;
    }
    return length;
}


/**
 * returns the value of the given String
 * @param str1 - the string
 * @return the content of str1
 */
const char* cString(const MyStringP str1)
{
    if(str1 == NULL)
    {
        return NULL;
    }
    return str1->str;
}


/**
 * checks to see if str2 is a substring of str1 starting from index index
 * @param str1 the string
 * @param str2 the substring
 * @param index the index to start from.
 * @param isCyclic != 0 - search also for cyclic appearnce
 * @return True if str2 is substring in str1 starting from index i false otherwise
 */
static int isSubStr(const MyStringP str1, const MyStringP str2, int index, int isCyclic)
{
    assert(str1 != NULL && str2 != NULL);
    // p1 starts from str1->str[index]
    char *p1 = (str1->str) + index, *p2 = str2->str;

    // the condition below represents if we didnt get to end of str2 and
    // (we didnt get to end of str1 or isCyclic).
    while(*p2 != '\0')
    {
        if(*p1 == '\0')
        {
            if(isCyclic)
            // this means that isCyclic is true so we just make p1
            // go back to the beginning.
            {
                p1 = str1->str;
            }
            else    //meaning we got to end of str1 first and isCyclic == 0
            {
                return 0;
            }
        }
        if(*p1 != *p2)
        {
            return 0;
        }
        p1++;
        p2++;

    }
    printf("True\n");

    // if we get here then we know that it is a substring ,otherwise we would
    // have returned 0 already. We got to the end of str2 with no return.
    return 1;
}


/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearnce
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const MyStringP str1, const MyStringP str2, int isCyclic)
{
    if(str1 == NULL || str2 == NULL)
    {
        return (unsigned int) ERROR_CODE;
    }
    unsigned int times = 0;
    unsigned int i, length = lengthString(str1);
    for(i = 0; i < length; i++)
    {
        if(isSubStr(str1, str2, i, isCyclic))
        {
            times += 1;
        }
    }
    return times;
}


/**
 * compares the 2 Strings by this logic:
 * compares the 2 strings by the first unmatched char.
 *
 * @param str1 the first string to compare
 * @param str2 the second string to compare
 * @return
 * 1 if the ASCII value of first unmatched character is greater in str1 then str2.
 * 0 if both strings are identical (equal)
 * -1 if the ASCII value of first unmatched character is less in str1 then str2.
 */
int cmpString(const MyStringP str1, const MyStringP str2)
{
    if(str1 == NULL || str2 == NULL)
    {
        return ERROR_CODE;
    }
    char *p1 = str1->str, *p2 = str2->str;
    while(*p1 == *p2)
    {
        if(*p1 == '\0' && *p2 == '\0')
        {
            return 0;
        }
        p1++;
        p2++;
    }
    if(*p1 > *p2)
    {
        return 1;
    }
    if(*p1 < *p2)
    {
        return -1;
    }
    // if we get to here then there is some error that happened
    return ERROR_CODE;
}


/**
 * concatenate the 2 Strings in to one String
 * @param str1 the first string in the result, the method will change the value of str1
 * @param str2 the second string in the result
 * @return the result of the concatenate
 */
MyStringP concatString(MyStringP str1, const MyStringP str2)
{
    if(str1 == NULL || str2 == NULL)
    {
        return NULL;
    }
    str1->str = (char *) realloc(str1->str,
            (lengthString(str1) + lengthString(str2) + 1) * sizeof(char));
    //the next line makes p a pointer to where the \0 char is in str1
    char *p1 = str1->str + lengthString(str1);
    char *p2 = str2->str;
    while(*p2 != '\0')
    {
        *p1 = *p2;
        p1++;
        p2++;
    }
    // we didnt set \0 yet and p1 is in the last allocated memory spot now
    *p1 = '\0';
    return str1;
}


/**
 * deletes a certain char from the String
 * @param str1 the string, changes his value according to the result
 * @param letter the letter to delete from the String
 * @return the result.
 */
MyStringP deleteCharString(MyStringP str1, const char letter)
{
    if(str1 == NULL)
    {
        return NULL;
    }
    char *p = str1->str;
    while(*p != '\0')
    {
        if(*p == letter)
        {
            char *temp = p;
            while(temp != '\0')
            {
                *temp = *(temp + 1);
                temp++;
            }
        }
        else
        {
            p++;
        }
    }
    // the next line frees any memory we have gotten ride of
    str1->str = (char *) realloc(str1->str, (lengthString(str1) + 1) * sizeof(char));
    return str1;
}