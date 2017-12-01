#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "array-util.h"
#include "serial-sorting.h"

int main(int argc, char** argv)
{
  int myRank, numProcs;
  int *data, *myArray, size, chunk;
  double start, end;
  
  MPI_Init(&argc, &argv);
  
  
  if (argc != 2)
  {
    fprintf(stderr, "Usage: <array size>\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);	

  size = atoi(argv[1]);
  chunk = size / numProcs;
  
  if (myRank == 0)
  {
    data = makeArray(size);
    start = MPI_Wtime();
  }
  
  myArray = (int *)malloc(chunk * sizeof(int));
  
  MPI_Scatter(data, chunk, MPI_INT, myArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);
  
  quickSort(myArray, 0, chunk - 1);
  
  MPI_Gather(myArray, chunk, MPI_INT, data, chunk, MPI_INT, 0, MPI_COMM_WORLD);
  
  if (myRank == 0)
  {
    quickSort(data, 0, size - 1);
    
    end = MPI_Wtime();
    printArray(data, size);
    printf( "Elapsed time is %f\n", end - start ); 
    
    free(data);
  }
  
  free(myArray);
  
  MPI_Finalize();
  return 0;
}
