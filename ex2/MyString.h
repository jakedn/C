/**
 * The header file for the countSubStr function.
 */


#ifndef COUNT_SUB_STR_H
#define COUNT_SUB_STR_H

#include <stdio.h>

/**
 * the MyString struct
 * */
typedef struct MyString * MyStringP;

/**
 * allocates a new String containing the str1 char*
 * @param str1 a char*
 * @return a new MyString * struct contaning str1
 */
MyStringP createStringFromChars(const char* str1);

/**
 * allocates a new String which is a copy of str1
 * @param str1 a String
 * @return a copy of str1
 */
MyStringP createStringFromString(const MyStringP str1);

/**
 * frees the allocated memory given to the struct
 * @param str1 the string to free
 */
void freeString(MyStringP str1);

/**
 * returns the lenght of the given String
 * @param str1 - the string
 * @return lenght of str1
 */
unsigned int lengthString(const MyStringP str1);

/**
 * returns the value of the given String
 * @param str1 - the string
 * @return the content of str1
 */
const char* cString(const MyStringP str1);

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
int cmpString(const MyStringP str1,const MyStringP str2);

/**
 * concatenate the 2 Strings in to one String
 * @param str1 the first string in the result, the method will change the value of str1
 * @param str2 the second string in the result
 * @return the result of the concatenate
 */
MyStringP concatString(MyStringP str1,const MyStringP str2);

/**
 * deletes a certain char from the String
 * @param str1 the string, changes his value according to the result
 * @param letter the letter to delete from the String
 * @return the result.
 */
MyStringP deleteCharString(MyStringP str1,const char letter);

/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearnce 
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const MyStringP str1, const MyStringP str2, int isCyclic);

#endif

