/*
 * Collection of serial sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 
 void bubbleSort(int size, int* array)
 {
    int i, j, swap;
    
    for (i = 0; i < size - 1; i++)
    {
       for (j = 0; j < size - 1; j++)
       {
          if (array[j] > array[j + 1])
          {
             int temp = array[j]
             array[j] = array[j + 1];
             array[j + 1] = temp;
             
             swap = 1;
          }
       }
       
       if (!swap) break;
    }
 }
