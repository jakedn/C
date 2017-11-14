/*File:FindString
 *Author:jakedn
 *
 *TODO
 */
#include <stdio.h>
#include <ctype.h>
#define ARGUMENT_ERROR_MSG "not enough arguments!"
#define HIT_END 2
#define HIT_END_NULL -1
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 256
//TODO document code
/**
 *
 * @param str - pointer to string we put the input into
 * @return - 1 if we succeeded 0 if there was an error and 2 if we hit EOF
 *              and -1 if we didnt read anything before we hit the end.
 */
int get_input(char *const str) {
    char next=' ',arrnext[2];
    while(next == ' ') {
        if (fgets(arrnext, 2, stdin) == NULL) { return HIT_END_NULL; }
        next = *arrnext;
    }
    if(next == '\n' || next == EOF){return HIT_END_NULL;}
    int c = 0;
    while (c<MAX_SIZE){
        //the next to lines replace getchar() because i dont have to cast the result
        //from int to char
        if(c != 0)
        {
            if(fgets(arrnext,2,stdin) == NULL){return HIT_END;}
            next = *arrnext;
        }
        if( next == '\n')
        {
            str[c] = '\0';
            return HIT_END;
        }
        if(next == ' ') { break; }
        if(!isprint(next))
        {
            fprintf(stderr,"Invalid input");
            return FALSE;
        }
        str[c++] = next;
    }
    str[c] = '\0';
    return TRUE;
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

/**
 *
 * @param line
 * @return
 */
char *updateLine(char *const line)
{
    int c=0;
    while(line[c] != '\0')
    {
        if(line[c] == '\n')
        {
            line[c] = '\0';
            break;
        }
        c++;
    }
    return line;
}

/**
 *
 * @param file_path
 * @param line
 * @param onlyFile
 */
void printLine(const char *file_path,char *const line,int onlyFile)
{
    if(onlyFile){printf("%s\n",updateLine(line));}
    else{printf("%s:%s\n",file_path,updateLine(line));}
}

/**
 *
 * @param file_path
 */
void printError(const char *file_path)
{
    fprintf(stderr,"grep: %s: No such file or directory\n",file_path);
}

int main(){

//    char *line,*word,a[256],b[256];
//    line=a;
//    word=b;
//    printf("%s in line %s :%d",word,line,isWordFound(word,line));
    int oneFile = FALSE;
    char file_path[MAX_SIZE+1],word[MAX_SIZE+1],line[MAX_SIZE+1];
    int get = get_input(word);
    if(get == HIT_END || get == HIT_END_NULL)
    {
        fprintf(stderr,ARGUMENT_ERROR_MSG);
        return 1;
    }
    get = get_input(file_path);
    if(get == HIT_END_NULL)
    {
        fprintf(stderr,ARGUMENT_ERROR_MSG);
        return 1;
    }
    if(get == HIT_END) {oneFile = TRUE;}
    FILE *f;
    int first = 1;
    do
    {
        if(!first)
        {
            get = get_input(file_path);
            if (get == HIT_END_NULL) { break; }
        }
        else{first = 0;}
        f = fopen(file_path, "r");
        if(f == NULL){printError(file_path);}
        else
        {
            while (fgets(line, MAX_SIZE + 1, f) != NULL)
            {
                if (isWordFound(word, line)) { printLine(file_path, line, oneFile); }
            }
            if (fclose(f) == EOF) { return 1; }//TODO error message
        }
    }while(get != HIT_END && get != HIT_END_NULL);

    return 0;
    get_input(file_path);
    printf("input : %s\n",file_path);
    get_input(file_path);
    printf("input : %s\n",file_path);
}