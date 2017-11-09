#include <stdio.h> 

#define NUM_OF_LINES 10

int main() 
{ 
  int n=0;
  int c;
  while( (c = getchar()) != EOF && (n < NUM_OF_LINES) )
    {
      putchar(c);
      if( c == '\n')
	{
	  n++;
	}
    }
  return 0;
}
