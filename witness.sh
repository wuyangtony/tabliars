#!/bin/sh

# This script counts reliable witnesses of all 3-carmichaels up to 10^(input)
# written by Andrew Shallue, Jan 2014

# email address for notification
#PBS -M ashallue@iwu.edu

# overall job name
#PBS -N witness

# limit walltime to 2 days
#PBS -l walltime=48:00:00

# change directory
cd ~ashallue/counting_liars

# creation of job array, variable is PBS_ARRAYID
##PBS -t 3-7

#change directory
cd ~ashallue/counting_liars

#run the command
LD_LIBRARY_PATH=/share/apps/lib64 ./runwitness 8 
