CC=gcc
# CC=c99-gcc
CPP=g++
OPTCFLAGS=-O3
CFLAGS=-g -Wall
OMPCFLAGS=-g -Wall -fopenmp
DBGCFLAGS=-g -Wall -DDBG
DBG2CFLAGS=-g -Wall -DDBG2

LIBS=-lgsl -lgslcblas -lm
EXES=DotProduct omp_mm ltyak00 ilyak01 ilyak02

# DotProduct: I think this was the example file (say, to be used as guidance) for the OpenMP assignment 4.
# # However, in 2019, quite alot of warnings, especially with gettime of day.
DotProduct: DotProduct.c
	${CC} ${OMPCFLAGS} -o $@ $^

# omp_mm, I can verify with v, high certainty that this was the assignment 4 handup. There seems to have been a certain amoutn of rush to it, and it may have started as a skeleton, because there is a name credited to the code.
# It's hard to say. In any case this was a course which prepared for MPI, so OpenMP was seen as somewhat inferior and perhaps was rushed through anyway.
omp_mm: omp_mm.c
	${CC} ${OMPCFLAGS} -o $@ $^

# as usual some stuff from internet course examples
bowd0: bowd0.c
	${CC} ${OMPCFLAGS} -o $@ $^

ilyak00: ilyak00.cpp
	${CPP} ${OMPCFLAGS} -o $@ $^

ilyak01: ilyak01.cpp
	${CPP} ${OMPCFLAGS} -o $@ $^

ilyak02: ilyak02.cpp
	${CPP} ${OMPCFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXES}
