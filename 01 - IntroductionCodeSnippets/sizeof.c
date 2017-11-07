/* A program that prints variable sizes */
#include <stdio.h>

int main()
{ 
  // Basic primitive types
  printf("Size of char %lu\n", sizeof(char));
  printf("Size of short %lu\n", sizeof(short));
  printf("Size of int %lu\n", sizeof(int));
  printf("Size of long %lu\n", sizeof(long));

  printf("Size of float %lu\n", sizeof(float));
  printf("Size of double %lu\n", sizeof(double));

  // other types
  printf("Size of long double %lu\n", sizeof(long double));

  return 0;
}
