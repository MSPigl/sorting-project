#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "array-util.h"

int main(int argc, char* argv)
{
		int myRank, numProcs;
		int myStart, myEnd, size, myCount;
		int* myArray, data;
		
		MPI_Init(&argc, &argv);
		
		if (argc != 2)
  	{
    		fprintf(stderr, "Usage: <array size>, %d were provided", argc - 1);
    		MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		size = atoi(argv[1]);
		
		if (size % numProcs != 0)
		{
				fprintf(stderr, "numProcs must evenly divide array size");
				MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
  	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
		
		if (myRank == 0)
		{
				//set up array
				
				data = makeArray(size);
		}
		
		myArray = (int *)malloc(sizeof(int) * size/numProcs);
		
		MPI_Scatter(data, size/numProcs, MPI_INT, &myArray, size/numProcs, MPI_INT, 0, MPI_COMM_WORLD);
		
		bubbleSort(myArray, size/numProcs);
		
		MPI_Scatter(&myArray, size/numProcs, MPI_INT, data, size/numProcs, MPI_INT, 0, MPI_COMM_WORLD);
		
		MPI_Finalize();
		return 0;
}
