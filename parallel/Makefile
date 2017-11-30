# Makefile for serial sorting algorithms
# Matt Pigliavento
# Siena College, Fall 2017

CFILES=array-util.c serial-sorting.c parallelBubble-mpi.c timer.c
OFILES=$(CFILES:.c=.o)
CC=mpicc

serial-test:	$(OFILES)
	$(CC) -o serial-test $(OFILES)

clean::
	/bin/rm -f serial-test $(OFILES)
