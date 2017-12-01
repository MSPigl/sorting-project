# Makefile for MPI implementation of quicksort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c quicksort-mpi.c timer.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o quicksort $(OFILES)

clean::
	/bin/rm -f quicksort $(OFILES)
