# Makefile for MPI implementation of bitonic sort
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c bitonicSort-mpi.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o bitonicSort $(OFILES) -lm

clean::
	/bin/rm -f bitonicSort $(OFILES)
