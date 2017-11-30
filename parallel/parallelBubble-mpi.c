#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "array-util.h"
//#include "serial-sorting.h"

 void bubbleSort(int arr[], int size)
 {
    int i, j, swap;
    
    for (i = 0; i < size - 1; i++)
    {
       printf("[%d] (%d, %d)\n", arr[i] i, j);
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

int main(int argc, char** argv)
{
		int myRank, numProcs;
		int i, size, chunk;
		int* myArray, *data;
		
		MPI_Init(&argc, &argv);
		
		if (argc != 2)
		{
    		fprintf(stderr, "Usage: <array size>, %d were provided", argc - 1);
    		MPI_Abort(MPI_COMM_WORLD, 1);
		}
		printf("Casting argument to int\n");
		size = atoi(argv[1]);
		printf("Argument casted to int (%d)\n", size);
		printf("Setting up MPI variables\n");
		MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
		printf("Set up MPI variables\n");
		if (size % numProcs != 0)
		{
				fprintf(stderr, "numProcs must evenly divide array size");
				MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		chunk = size/numProcs;
		myArray = (int *)malloc(sizeof(int) * chunk);
	
		if (myRank == 0)
		{
				printf("Preparing to generate array\n");
				//set up array
				data = makeArray(size);
				printf("Size is %d\n", size);
		}
		
		MPI_Barrier(MPI_COMM_WORLD);
		printf("%d | Scattering\n\n", myRank);
		MPI_Scatter(data, chunk, MPI_INT, &myArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);
		printf("%d | Sorting\n\n", myRank);
		bubbleSort(myArray, chunk);
		printf("%d | Sorted\n\n", myRank);
		MPI_Gather(&myArray, chunk, MPI_INT, data, chunk, MPI_INT, 0, MPI_COMM_WORLD);
		
		if (myRank == 0)
		{
				mergeSort(data, 0, size - 1);
				printArray(data, size);
		}
		
		MPI_Finalize();
		return 0;
}
