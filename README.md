# Intro

OpenMP promises paralleleism with the low level inconveniences of pthreads
and without the message passing complications of MPI.

Undoubted this is at a cost in elegance, debugging clarity etc., but the win in speed of implementation
is hard to contest.

This repo stores some examples of how to use it.

## General

The number of threads can be defined with an environment variable:

 export OMP_NUM_THREADS=4

# From PP course 2007.

## omp_mm 
This was meant to be assignement 4. It seems, and I almost recall, that it was rushed.

## bowd0
THi is a good example for starters. SHows how a parallel region must be announced first
which is to be encolsed in braces. There's an opporunity to define the scope of variable to follow there, in MPI terms by having shared it's a way of passing the certain variables around.

While this is an elementary example it's clear, the main object will be a loop so after the parallel region delcaration you get the pragma omp for, so the pattern of how things usually play out code wise is already there.

pthread
I've included this in here because things have become fuzzier and fuzzier between pthreads and openmp
It was for msc 2007, but I have a strgon recall of going over it all again in Vigo, and indeed
the datge on it seems geuine:
Sep 11  2012
