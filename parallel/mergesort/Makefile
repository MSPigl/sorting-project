# Makefile for MPI implementation of mergesort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c mergesort-mpi.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o mergesort $(OFILES)

clean::
	/bin/rm -f mergesort $(OFILES)
