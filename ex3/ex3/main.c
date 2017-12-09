#include <stdio.h>
#include <stdlib.h>
void ReadFile(FILE *fIn)

{

    char nextLine[200];

    while(!feof(fIn))

    {

        fscanf(fIn,"%s",nextLine);

        printf("%s\n",nextLine);

    }

}
int main() {
    fprintf(stderr, MEM_OUT);
}