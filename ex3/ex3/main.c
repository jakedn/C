#include <stdio.h>

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
    FILE *f = fopen("./h.txt","r");
    if (f == NULL){printf("hithere");}
    ReadFile(f);
    return 0;
}