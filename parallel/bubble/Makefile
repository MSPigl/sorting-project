# Makefile for MPI implementation of bubble sort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c bubbleSort-mpi.c timer.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o serial-test $(OFILES)

clean::
	/bin/rm -f serial-test $(OFILES)
