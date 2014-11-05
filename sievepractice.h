/* function declarations for the 
sieve of eratosthenes
*/

#ifndef SIEVEPRACTICE_H
#define SIEVEPRACTICE_H
#include <NTL/ZZ.h>
#include <vector>
#include <NTL/ZZ.h>

NTL_CLIENT  // replaces namespace std

/*Function that iterates through sieve marking slots as 1 for composite*/
long mark(vector<long> &sieve);

/*Function that iterates through sieve and prints out primes*/
long primes(vector<long> &sieve);

#endif //SIEVEPRACTICE_H
