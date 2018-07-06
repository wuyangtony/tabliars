#!/bin/sh

# This script built for counting integers with exactly two strong liars
# Written by Andrew Shallue, July 2013

# email address for notifications
#PBS -M ashallue@iwu.edu

# job name
#PBS -N countingliars

# limit walltime to 2 days
#PBS -l walltime=48:00:00


# change directory
cd ~ashallue/counting_liars

# run the command
LD_LIBRARY_PATH=/share/apps/lib64 ./runtwostrongliars

