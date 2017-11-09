/* A program that prints variable sizes */
#include <stdio.h>

long power(int base, int n);

int main()
{ 
  // Basic primitive types
  printf("Max char value is %ld\n", power(2, 8*sizeof(char) - 1) - 1);
  printf("Max short value is %ld\n", power(2, 8*sizeof(short) - 1) - 1);
  printf("Max int value is %ld\n", power(2, 8*sizeof(int) - 1) - 1);
  printf("Max long value is %ld\n", power(2, 8*sizeof(long) - 1) - 1);

  return 0;
}

long power( int base, int n )
{
  int i;
  long p = 1;
  for( i = 0; i < n; i++ )
    {
      p = p * base;
    }
  return p;
}
