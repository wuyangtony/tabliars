/*function declarations for the
sieve that saves lowest primes
in the array*/

#ifndef LOWESTPRIMESIEVE_H
#define LOWESTPRIMESIEVE_H	
#include <NTL/ZZ.h>
#include <vector>

NTL_CLIENT //replaces namespace std

/*Function that iterates through sieve marking slots as lowest prime if composite*/
long lowestprime(vector<long> &sieve);

/*Function that iterates through sieve and prints out primes*/
long prime(vector<long> &sieve); 

#endif
