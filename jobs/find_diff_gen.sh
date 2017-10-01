#!/bin/sh
# This is to find the first prime number p such that the multiplicative groups mod p and p squared have different first generators. 
#If Hyperion cannot find such prime within the range of 2^30 or within the pre-specified runtime limit, then I recommend we start to prove Tony's conjecture.
#
# 34 hours runtime requested
#PBS -l walltime=34:00:00
#
# job name: tony_test2
#PBS -N tony_test2
#
# email address for notification
#PBS -M wliu@iwu.edu

# change working directory
cd ~/tabliars

# run the executable
./testtonysconjecture
