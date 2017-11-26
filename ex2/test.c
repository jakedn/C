#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"

int main()
{
    char arr[4] = "abc";
    char arr2[4] = "def";
    MyStringP a = createStringFromChars(arr);
    MyStringP b = createStringFromChars(arr2);
    MyStringP c = concatString(a,b);
    printf("%s\n%s\n%s\n",cString(a),cString(b),cString(c));
    freeString(a);
    freeString(b);

}