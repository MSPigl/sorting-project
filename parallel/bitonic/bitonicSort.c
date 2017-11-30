/*
 * MPI implementation of the bitonic sort algorithm
 * (Based on the implementation by Github user adrianlee)
 *
 * Matt Pigliavento
 * Siena College, Fall 2017
 */

#include <stdio.h>      
#include <stdlib.h>
#include <math.h>
#include <mpi.h>    

#include "array-util.h"
#include "serial-sorting.c"

int myRank, numProcs;
int *array;
int array_size;

int main(int argc, char * argv[]) {
    int i, j;
    double start, end;

    // Initialization, get # of processes & this PID/rank
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    // Initialize Array for Storing Random Numbers
    array_size = atoi(argv[1]) / numProcs;
    array = makeArray(array_size);

    // Cube Dimension
    int dimensions = log2(numProcs);

    // Start Timer before starting first sort operation (first iteration)
    if (myRank == 0) {

        start = MPI_Wtime();
    }

    // Sequential Sort
    //qsort(array, array_size, sizeof(int), ComparisonFunc);
    quickSort(array, 0, array_size);
    
    // Bitonic Sort follows
    for (i = 0; i < dimensions; i++) {
        for (j = i; j >= 0; j--) {
            // (window_id is even AND jth bit of process is 0)
            // OR (window_id is odd AND jth bit of process is 1)
            if (((myRank >> (i + 1)) % 2 == 0 && (myRank >> j) % 2 == 0) || ((myRank >> (i + 1)) % 2 != 0 && (myRank >> j) % 2 != 0)) {
                CompareLow(j);
            } 
            else {
                CompareHigh(j);
            }
        }
    }

    // Blocks until all processes have finished sorting
    MPI_Barrier(MPI_COMM_WORLD);

    if (myRank == 0) {
        end = MPI_Wtime();

        printArray(array, array_size);

        printf("Time Elapsed (Sec): %f\n", timer_end - timer_start);
    }

    // Reset the state of the heap from Malloc
    free(array);

    // Done
    MPI_Finalize();
    return 0;
}

int log2(int n)
{
  return log(n) / log(2);  
}

void CompareLow(int j) {
    int i, min;

    /* Sends the biggest of the list and receive the smallest of the list */

    // Send entire array to paired H Process
    // Exchange with a neighbor whose (d-bit binary) processor number differs only at the jth bit.
    int send_counter = 0;
    int * buffer_send = malloc((array_size + 1) * sizeof(int));
    MPI_Send(
        &array[array_size - 1],     // entire array
        1,                          // one data item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Receive new min of sorted numbers
    int recv_counter;
    int * buffer_recieve = malloc((array_size + 1) * sizeof(int));
    MPI_Recv(
        &min,                       // buffer the message
        1,                          // one data item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Buffers all values which are greater than min send from H Process.
    for (i = 0; i < array_size; i++) {
        if (array[i] > min) {
            buffer_send[send_counter + 1] = array[i];
            send_counter++;
        } else {
            break;      // Important! Saves lots of cycles!
        }
    }

    buffer_send[0] = send_counter;

    // send partition to paired H process
    MPI_Send(
        buffer_send,                // Send values that are greater than min
        send_counter,               // # of items sent
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // receive info from paired H process
    MPI_Recv(
        buffer_recieve,             // buffer the message
        array_size,                 // whole array
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Take received buffer of values from H Process which are smaller than current max
    for (i = 1; i < buffer_recieve[0] + 1; i++) {
        if (array[array_size - 1] < buffer_recieve[i]) {
            // Store value from message
            array[array_size - 1] = buffer_recieve[i];
        } else {
            break;      // Important! Saves lots of cycles!
        }
    }

    // Sequential Sort
    //qsort(array, array_size, sizeof(int), ComparisonFunc);
    quickSort(array, array_size);

    // Reset the state of the heap from Malloc
    free(buffer_send);
    free(buffer_recieve);

    return;
}

void CompareHigh(int j) {
    int i, max;

    // Receive max from L Process's entire array
    int recv_counter;
    int * buffer_recieve = malloc((array_size + 1) * sizeof(int));
    MPI_Recv(
        &max,                       // buffer max value
        1,                          // one item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Send min to L Process of current process's array
    int send_counter = 0;
    int * buffer_send = malloc((array_size + 1) * sizeof(int));
    MPI_Send(
        &array[0],                  // send min
        1,                          // one item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Buffer a list of values which are smaller than max value
    for (i = 0; i < array_size; i++) {
        if (array[i] < max) {
            buffer_send[send_counter + 1] = array[i];
            send_counter++;
        } else {
            break;      // Important! Saves lots of cycles!
        }
    }

    // Receive blocks greater than min from paired slave
    MPI_Recv(
        buffer_recieve,             // buffer message
        array_size,                 // whole array
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message receiveds
    );
    recv_counter = buffer_recieve[0];

    // send partition to paired slave
    buffer_send[0] = send_counter;
    MPI_Send(
        buffer_send,                // all items smaller than max value
        send_counter,               // # of values smaller than max
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Take received buffer of values from L Process which are greater than current min
    for (i = 1; i < recv_counter + 1; i++) {
        if (buffer_recieve[i] > array[0]) {
            // Store value from message
            array[0] = buffer_recieve[i];
        } else {
            break;      // Important! Saves lots of cycles!
        }
    }

    // Sequential Sort
    //qsort(array, array_size, sizeof(int), ComparisonFunc);
    quickSort(array, array_size);

    // Reset the state of the heap from Malloc
    free(buffer_send);
    free(buffer_recieve);

    return;
}
