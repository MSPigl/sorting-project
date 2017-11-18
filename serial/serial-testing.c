/*
 * Test serial implementations of sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 
 #include <stdio.h>
 
 #include "array-util.c"
 #include "serial-sorting.c"
 
 int main(int argc, char *argv)
 {
    int* myArray = makeArray(10);
    
    printf("Unsorted array: ");
    printArray(10, myArray);
    
    bubbleSort(10, myArray);
    
    printf("Sorted array: ");
    printArray(10, myArray);
 
    return 0;
 }
