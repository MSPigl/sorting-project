/*
 * Test serial implementations of sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 
 #include <stdio.h>
 #include <sys/time.h>
 
 #include "timer.h"
 #include "array-util.h"
 #include "serial-sorting.h"
 
 int main(int argc, char *argv)
 {
    struct timeval start, stop;
    
    int* myArray = makeArray(10);
    
    printf("\n\nBubble sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    gettimeofday(&start, NULL);
    bubbleSort(myArray, 10);
    gettimeofday(&stop, NULL);
  
    printf("Sorted array: ");
    printArray(myArray, 10);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
  
    myArray = makeArray(10);
  
    printf("\n\nBitonic sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    gettimeofday(&start, NULL);
    bitonicSort(myArray, 10);
    gettimeofday(&stop, NULL);  
  
    printf("Sorted array: ");
    printArray(myArray, 10);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
    
    myArray = makeArray(10);
  
    printf("\n\nQuicksort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    gettimeofday(&start, NULL);
    quickSort(myArray, 0, 9);
    gettimeofday(&stop, NULL);
  
    printf("Sorted array: ");
    printArray(myArray, 10);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
  
    myArray = makeArray(10);
  
    printf("\n\nMergesort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    gettimeofday(&start, NULL);
    mergeSort(myArray, 0, 9);
    gettimeofday(&stop, NULL);  
  
    printf("Sorted array: ");
    printArray(myArray, 10);
    printf("Sorting took %f seconds\n", diffgettime(start,stop));
 
    return 0;
 }
