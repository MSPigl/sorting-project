/*
 * Test serial implementations of sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/time.h>
 
 #include "timer.h"
 #include "array-util.h"
 #include "serial-sorting.h"
 
 int main(int argc, char *argv)
 {
    int size;
    if (argc != 2) 
    {
       size = 32;
    }
    else 
    {
       size = (int) (argv[1]);
    }
  
    struct timeval start, stop;
    
    int* myArray = makeArray(size);
    
    printf("\n\nBubble sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, size);
    
    gettimeofday(&start, NULL);
    bubbleSort(myArray, size);
    gettimeofday(&stop, NULL);
  
    printf("Sorted array: ");
    printArray(myArray, size);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
  
    myArray = makeArray(size);
  
    printf("\n\nBitonic sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, size);
    
    gettimeofday(&start, NULL);
    bitonicSort(myArray, size);
    gettimeofday(&stop, NULL);  
  
    printf("Sorted array: ");
    printArray(myArray, size);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
    
    myArray = makeArray(size);
  
    printf("\n\nQuicksort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, size);
    
    gettimeofday(&start, NULL);
    quickSort(myArray, 0, size - 1);
    gettimeofday(&stop, NULL);
  
    printf("Sorted array: ");
    printArray(myArray, size);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
  
    myArray = makeArray(size);
  
    printf("\n\nMergesort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, size);
    
    gettimeofday(&start, NULL);
    mergeSort(myArray, 0, size - 1);
    gettimeofday(&stop, NULL);  
  
    printf("Sorted array: ");
    printArray(myArray, size);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
 
    return 0;
 }
