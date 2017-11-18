/*
 * Test serial implementations of sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 
 #include <stdio.h>
 
 #include "array-util.h"
 #include "serial-sorting.h"
 
 int main(int argc, char *argv)
 {
    int* myArray = makeArray(10);
    
    printf("\n\nBubble sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    bubbleSort(myArray, 10);
    
    printf("Sorted array: ");
    printArray(myArray, 10);
  
    myArray = makeArray(10);
  
    printf("\n\nBitonic sort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    bitonicSort(myArray, 10);
    
    printf("Sorted array: ");
    printArray(myArray, 10);
  
    myArray = makeArray(10);
  
    printf("\n\nQuicksort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    quickSort(myArray, 0, 9);
    
    printf("Sorted array: ");
    printArray(myArray, 10);
  
    myArray = makeArray(10);
  
    printf("\n\nMergesort: \n\n");
  
    printf("Unsorted array: ");
    printArray(myArray, 10);
    
    mergeSort(myArray, 0, 9);
    
    printf("Sorted array: ");
    printArray(myArray, 10);
 
    return 0;
 }
