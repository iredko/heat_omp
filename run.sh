#!/bin/bash
gcc -fopenmp -O2 -std=c99 -o heat_omp main.c 

for i in {1..100}
do
    for j in {1..40}
    do
	echo "$(./heat_omp 400 800 6000 $j 293 1000)">>research.out
    done
done
