/*File:FindString
 *Author:jakedn
 */
#define LEN 5
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 256
#include <stdio.h>
#include <string.h>

char *get_input() {
    char *result;
    char r[LEN];
    result = r;
    int c = 0;
    while (c<LEN-1){

        printf("here\n");
        scanf("%c",(result+c++));
        printf("%c\n",result[c-1]);
    }
    result[c] = '\0';
    return result;
}

/**
 * this function checks to see if word is in the line line
 * @param word the word to search for
 * @param line the line we are searching in
 * @return 1 if true 0 if false
 */
int isWordFound(const char * const word,const char *line){
    int c=0;
    while(*line != '\0')
    {
        c=0;
        while(word[c] != '\0')
        {
            if(line[c] == '\0'){return FALSE;}
            if(word[c] == line[c]) { c++; }
            else{break;}
        }
        if(word[c] == '\0') { return TRUE; }
        line++;
    }
    return FALSE;
}

void printLine(const char *filepath, const char *line,int onlyFile)
{
    if(onlyFile){printf("%s\n",line);}
    else{printf("%s:%s\n",filepath,line);}
}

int main(){

//    char *line,*word,a[256],b[256];
//    line=a;
//    word=b;
//    printf("%s in line %s :%d",word,line,isWordFound(word,line));
    printf("input : %s\ninput:%s",get_input(),get_input());
}