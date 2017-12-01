# Makefile for MPI implementation of mergesort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c mergesort-mpi.c timer.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o mergesort $(OFILES)

clean::
	/bin/rm -f mergesort $(OFILES)
