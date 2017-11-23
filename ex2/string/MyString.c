#include <stdio.h>

typedef struct {
    char *str;
}string;

int lengthString(string str)
{
    int length = 0;
    int i=0;
    if(str.str == NULL)
        return length;
    while(str.str[i] != '\0')
        length++;
    return length;
}

int countSubStr(const string str1, const string str2, const int isCyclic)
{

}

int cmpString(const string str1, const string str2)
{
    int result;
    char *p1 = str1.str, *p2 = str2.str;
    while(*p1 == *p2)
    {
        if(p1 == '\0' && p2 == '\0')
        {
            return 0;
        }
        p1++;
        p2++;
    }

}