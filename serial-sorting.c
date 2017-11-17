/*
 * Collection of serial sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 #include <stdio.h>
 void bubbleSort(int size, int* array)
 {
    int i, j, swap;
    
    for (i = 0; i < size - 1; i++)
    {
       for (j = 0; j < size - 1; j++)
       {
          if (array[j] > array[j + 1])
          {
             int temp = array[j];
             array[j] = array[j + 1];
             array[j + 1] = temp;
             
             swap = 1;
          }
       }
       
       if (!swap) break;
    }
 }

void merge_up(int *arr, int n)
{
   int step=n/2,i,j,k,temp;
   while (step > 0)
   {
      for (i=0; i < n; i+=step*2) 
      {
         for (j=i,k=0;k < step;j++,k++)
         {
            if (arr[j] > arr[j+step])
            {
              // swap
              temp = arr[j];
              arr[j]=arr[j+step];
              arr[j+step]=temp;
            }
         }
      }
      step /= 2;
   }
}

void merge_down(int *arr, int n)
{
   int step=n/2,i,j,k,temp;
   while (step > 0)
   {
      for (i=0; i < n; i+=step*2)
      {
         for (j=i,k=0;k < step;j++,k++) 
         {
            if (arr[j] < arr[j+step])
            {
               // swap
               temp = arr[j];
               arr[j]=arr[j+step];
               arr[j+step]=temp;
            }
         }
      }
      step /= 2;
   }
}

void bitonicSort()
{
   
}

int main()
{
   int array[] = {5, 7, 1, 6, 2, 20, 35, 3, 9, 10}; 
   
   bubbleSort(10, array);
   int i;
   for (i = 0; i < 10; i++)
   {
     printf("%d ", array[i]);
   }
   printf("\n");
}
