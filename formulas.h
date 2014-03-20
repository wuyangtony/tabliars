#ifndef FORMULAS_H
#define FORMULAS_H

#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <list>
#include <vector>

NTL_CLIENT


/* returns the number of strong liars of n, using the definition, 
given by an NTL implementation */
ZZ StrongLiarCount(ZZ n);

/* returns the number of Strong liars of n.  It does this using 
the formula of Monier, not the definition */
long trialStrongLiarCount(long n);

/* returns the number of Fermat liars of n.  It does this using 
the formula of Monier, not the definition */
long FermatLiarCount(long n);

/* Similar to trialStrongLiarCount, but uses a 
sieving strategy which is more efficient.  Uses FactoredSieve
and sieveFactor below
Specifically, output is number of odd integers with 2 strong liars 
*/
long  sieveTwoStrongLiarsCount(long x);

/* this is a basic sieve of Erasthothenes.  It takes integers up to 
x and sieves by primes up to sievebound, and returns the integers not sieved.
That is, the output is the number of integers up to x not divisible 
by any of the primes up to sievebound */
long BasicSieve(long x, RR sievebound);

/*
This uses a sieve of Erasthothenes to factor all integers up to n
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
*/
vector<long> FactoredSieve(long n);

/* Since the factoredsieve stores only the largest prime factor, the 
next routine uses that information (with access to the entire sieve 
for recursive work) to give the full factorization
Input is the sieve and a vector which will store the factors
*/
void sieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* This next only returns the distinct prime factors of n */
void distinctsieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* returns the largest odd divisor of n */
long OddDivisor(long n);

/* returns ord_2(n), the largest power of 2 dividing n */
long Ord2(long n);

// Factor returns all the distinct prime factors of n, stored in the given list
// uses trial division
// written by Steven Hayman
void trialFactor(long n, list<long>& factors);

// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(long a, long n);


#endif  //FORMULAS_H
