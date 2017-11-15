/*File:FindString
 *Author:jakedn
 *
 *TODO
 */
#include <stdio.h>
#include <ctype.h>
#define ARGUMENT_ERROR_MSG "not enough arguments!\n"
#define HIT_END 2
#define HIT_END_NULL (-1)
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 256

/**
 * this method takes in str and makes its contents the next input that is string
 * until it reaches a ' ' or '\n' or EOF not including them in str.
 * @param str - pointer to string we put the input into
 * @return - 1 if we succeeded 0 if there was an error and 2 if we hit EOF
 *              and -1 if we didnt read anything before we hit the end.
 */
int get_input(char *const str) {
    char next=' ',arrnext[2];

    //this next part of code takes out redundant ' ' chars that are in the input.
    while(next == ' ') {
        if (fgets(arrnext, 2, stdin) == NULL) { return HIT_END_NULL; }
        next = *arrnext;
    }

    //if we hit the end of the input before we got anything of sustenance we return a special value to indicate that.
    if(next == '\n' || next == EOF){return HIT_END_NULL;}

    //this next part checks to see if every char is printable and appends it to str.
    //the loop will stop if it hits an error, gets to EOF or reads the maximal char length.
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
            fprintf(stderr,"Invalid input\n");
            return FALSE;
        }
        str[c++] = next;
    }
    str[c] = '\0';
    return TRUE;
}

/**
 * this function checks to see if two chars are the same (case insensitive)
 * @param a first char
 * @param b the second char
 * @return 1 if its the same char (case insensitive) otherwise 0.
 */
int isEqual(char a, char b)
{
    //tolower changes a char to lowercase or leaves it unchanged so either way
    //tolower(a) will only equal tolower(b) if a and b are the same letter
    if (isalpha(a)) { return tolower(a)==tolower(b); }
        //if a isnt a letter then we just check if they are the same char
    else {return a == b;}
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
            if(line[c] == '\0'){
                //we reached end of the line before completing the word
                return FALSE;
            }
            if(isEqual(word[c],line[c])) { c++; }
            else
            {
                //here we got to a place that line and word are different so word isnt in this part of line
                break;
            }
        }
        if(word[c] == '\0') { return TRUE; }
        line++;
    }
    return FALSE;
}

/**
 * this method takes in a string that represents a line in a file and takes
 * out the \n char and replaces it with a \0 char.
 * @param line - the string we want to update
 * @return - a pointer pointing to line.
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
 * this method prints otu a line from the file in file_path
 * @param file_path - a string that contains the files directory
 * @param line - a sting containing the contents of a line
 * @param onlyFile - 1 if the file is the only input file 0 otherwise
 */
void printLine(const char *file_path,char *const line,int onlyFile)
{
    if(onlyFile){printf("%s\n",updateLine(line));}
    else{printf("%s:%s\n",file_path,updateLine(line));}
}

/**
 * this method prints out the file non existing error
 * @param file_path - the files directory.
 */
void printError(const char *file_path)
{
    fprintf(stderr,"grep: %s: No such file or directory\n",file_path);
}

int main(){

    int oneFile = FALSE;

    //max_size+1 so we can add '\0' to the end of our string
    char file_path[MAX_SIZE+1],word[MAX_SIZE+1],line[MAX_SIZE+1];
    int got_input = get_input(word);

    if(got_input == HIT_END || got_input == HIT_END_NULL)
    {
        //if we get to EOF here we didnt get a file for input so we send a proper error message
        fprintf(stderr,ARGUMENT_ERROR_MSG);
        return 1;
    }
    got_input = get_input(file_path);
    if(got_input == HIT_END_NULL)
    {
        //also here we didnt get a file for input so we send a proper error message
        fprintf(stderr,ARGUMENT_ERROR_MSG);
        return 1;
    }
    if(got_input == HIT_END) {oneFile = TRUE;}
    FILE *f;
    int first = 1;
    do
    {
        //we have to keep track if its our first iteration otherwise we lose a char
        if(!first)
        {
            got_input = get_input(file_path);
            if (got_input == HIT_END_NULL) { break; }
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
            if (fclose(f) == EOF)
            {
                fprintf(stderr,"Couldnt close file: %s",file_path);
                return 1;
            }
        }
    }while(got_input != HIT_END && got_input != HIT_END_NULL);

    return 0;
}