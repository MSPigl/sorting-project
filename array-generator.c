#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * Function to fill an array with pseudo-random integers
 */
int* fillArray(int size, int* array)
{
   srand(time(NULL));
   int r, i; 
   for (i = 0; i < size; i++)
   {
      r = rand();
      array[i] = r;
   }
}

/*
 * Function to generate input arrays
 */
int* makeArray(int size)
{
   int* array = (int *)malloc(numElement * sizeof(int));
   fillArray(size, array);
   
   return array;
}

int main()
{
   int* intArray = makeArray(10, sizeof(int));
   
   int i;
   printf("{ ");
   for (i = 0; i < 10; i++)
   {
      printf("%d ", intArray[i]);
   }
   printf("}\n");
}
