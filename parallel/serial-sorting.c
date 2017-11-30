/*
 * Collection of serial sorting algorithms
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */
 #include <stdio.h>
 void bubbleSort(int arr[], int size)
 {
    int i, j, swap;
    
    for (i = 0; i < size - 1; i++)
    {
       for (j = 0; j < size - 1; j++)
       {
          if (arr[j] > arr[j + 1])
          {
             int temp = arr[j];
             arr[j] = arr[j + 1];
             arr[j + 1] = temp;
             
             swap = 1;
          }
       }
       
       if (!swap) break;
    }
 }

void merge_up(int arr[], int n)
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

void merge_down(int arr[], int n)
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

void bitonicSort(int arr[], int size)
{
   int i, j;
   for (i = 2; i <= size; i *= 2)
   {
      for (j = 0; j < size;) 
      {
         merge_up((arr + j), i);
         merge_down((arr + j + i), i);
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
 
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;

    int L[n1];
    int R[n2];
 
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
 
    i = 0;
    j = 0; 
    k = left; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
   if (left < right)
   {
      int mid = (left + right) / 2;
    
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);
    
      merge(arr, left, mid, right);
   }
}

/*
int main()
{
   int array[] = {5, 7, 1, 6, 2, 20, 35, 3, 9, 10}; 
   
   //bubbleSort(10, array);
   //bitonicSort(10, array);
   //quickSort(array, 0, 9);
   mergeSort(array, 0, 9);
   int i;
   for (i = 0; i < 10; i++)
   {
     printf("%d ", array[i]);
   }
   printf("\n");
}
*/
