# Makefile for MPI implementation of bubble sort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c bubbleSort-mpi.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o bubbleSort $(OFILES)

clean::
	/bin/rm -f bubbleSort $(OFILES)
