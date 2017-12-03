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
		double t1, t2;
		int* myArray, *data;
		
		MPI_Init(&argc, &argv);
		
		if (argc != 2)
		{
    		fprintf(stderr, "Usage: <array size>, %d were provided", argc - 1);
    		MPI_Abort(MPI_COMM_WORLD, 1);
		}

		size = atoi(argv[1]);

		MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	
		if (size % numProcs != 0)
		{
				fprintf(stderr, "numProcs must evenly divide array size");
				MPI_Abort(MPI_COMM_WORLD, 1);
		}
		
		chunk = size/numProcs;
		myArray = (int *)malloc(chunk * sizeof(int));
		
		if (myRank == 0)
		{
				//set up array
				data = makeArray(size);
				t1 = MPI_Wtime();
		}

		MPI_Scatter(data, chunk, MPI_INT, myArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);

		bubbleSort(myArray, chunk);

		MPI_Gather(myArray, chunk, MPI_INT, data, chunk, MPI_INT, 0, MPI_COMM_WORLD);
		
		if (myRank == 0)
		{
				//mergeSort(data, 0, size - 1);
				bubbleSort(data, size);
				t2 = MPI_Wtime();
				printf( "Elapsed time is %f\n", t2 - t1 ); 
				free(data);
		}
	
		free(myArray);
		
		MPI_Finalize();
		return 0;
}
