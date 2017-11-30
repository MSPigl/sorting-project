/*
 * Functions to generate and fill an integer array to be used as input for sorting algorithms
 * 
 * Matt Pigliavento
 * Siena College, Fall 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * Function to fill an array with pseudo-random integers
 */
void fillArray(int* array, int size)
{
   srand(time(NULL));
   int r, i; 
   for (i = 0; i < size; i++)
   {
      r = rand() % (size * size);
      array[i] = r;
   }
}

/*
 * Function to generate input arrays
 */
int* makeArray(int size)
{
   int* array = (int *)malloc(size * sizeof(int));
   fillArray(array, size);
   
   return array;
}

void printArray(int* array, int size)
{
   int i;
   
   printf("{ ");
   for (i = 0; i < size - 1; i++)
   {
      printf("%d, ", array[i]);
   }
   printf("%d }\n", array[size - 1]);
}
