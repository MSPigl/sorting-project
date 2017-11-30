#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "array-util.h"
#include "serial-sorting.h"

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
	        printf("%d | element at 0: %d\n", myRank, myArray[0]);
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
