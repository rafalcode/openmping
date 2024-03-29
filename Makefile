CC=gcc
# CC=c99-gcc
CPP=g++
OPTCFLAGS=-O3
CFLAGS=-g -Wall
OMPCFLAGS=-g -Wall -fopenmp
DBGCFLAGS=-g -Wall -DDBG
DBG2CFLAGS=-g -Wall -DDBG2

LIBSTHRE=-lpthread
LIBS=-lgsl -lgslcblas -lm
EXES=DotProduct omp_mm mmjn ltyak00 ilyak01 ilyak02 ilyak02_ mmm_unroll mmnorm_pth2 testdgemm example_user

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

# OK, filling the vector of strings
# this proved a little cagey, I decided I needed to use a for loop inside
ilyak02: ilyak02.cpp
	${CPP} ${OMPCFLAGS} -o $@ $^
# but once i orted out how bad c++ was with formatting, and started to use sprint, then I managed to do a proper version.
ilyak02_: ilyak02_.cpp
	${CPP} ${OMPCFLAGS} -o $@ $^

# from 13 March 2010
mmjn: mmjn.c
	${CC} ${CFLAGS} -o $@ $^ ${LIBSTHRE}
mmjn_omp: mmjn_omp.c
	${CC} ${OMPCFLAGS} -o $@ $^

# OK< here we go back to 2007 and some assignment code demonstrating the different
# ways matrix multiplication can be done to make it faster.
# I start with the simplest (pair) unroll which is almost the same as the naive version
# and then do an npenmp version. Actually it's enough to demonstrate how simple openmp is to apply
# and also shows it gives the necessary speed up (with 4 threads it will be 4 times as fast)>
mmm_unroll: mmm_unroll.c
	${CC} ${CFLAGS} -o $@ $^
mmmunr_omp: mmmunr_omp.c
	${CC} ${OMPCFLAGS} -o $@ $^

# pthreads is now part o of libc ... so it needs nothign extra ...
mmnorm_pth2: mmnorm_pth2.c
	${CC} ${CFLAGS} -o $@ $^

# testing basic blas stuff.
# where did this file come from? Dunno, pilfered from somewhere.
testdgemm: testdgemm.cc
	${CPP} ${CFLAGS} -o $@ $^ -lblas

example_user: example_user.c
	# ${CPP} ${CFLAGS} -o $@ $^ -lmkl_rt
	${CPP} ${CFLAGS} -o $@ $^ -llapack

.PHONY: clean

clean:
	rm -f ${EXES}
