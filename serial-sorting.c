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

void bitonicSort(int size, int* array)
{
   int i, j;
   for (i = 2; i <= size; i *= 2)
   {
      for (j = 0; j < size;) 
      {
         merge_up((array + j), i);
         merge_down((array + j + i), i);
         j += i * 2;
      }
   }
}
 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int index = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}

int main()
{
   int array[] = {5, 7, 1, 6, 2, 20, 35, 3, 9, 10}; 
   
   //bubbleSort(10, array);
   //bitonicSort(10, array);
   quicksort(array, 0 9);
   int i;
   for (i = 0; i < 10; i++)
   {
     printf("%d ", array[i]);
   }
   printf("\n");
}
