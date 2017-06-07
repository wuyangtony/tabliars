#ifndef FORMULAS_H
#define FORMULAS_H

#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <list>
#include <vector>
#include <math.h>

NTL_CLIENT

/*
This uses a sieve of Erasthothenes to factor all integers up to n
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
@para		x: a positive integer
@return		a vector of first prime factors
*/
vector<long> FactoredSieve(long x);

/* 
This is a poly time algorithm, but currently it is a loglog factor slower 
than theoretically possible since I do not use precomputation in exp.
@para		a: 	the base number
		n:	the modulo number
		sieve: 	a constant reference to a vector of factored sieve
@return		multiplicative order of a mod n
*/
long MulOrder(long a, long n, const vector<long>& sieve);

/*
This funtion finds the first generator of a multiplicative group
@para		p_power: a prime power
		sieve:   a constant reference to a vector of factored sieve
@return		the first generatort for mult group mod p_power
*/
long firstGenerator(long p_power, const vector<long> sieve);

/* returns the number of strong liars of n, using the definition, 
given by an NTL implementation */
ZZ StrongLiarCount(ZZ n);

/* returns the number of Strong liars of n.  It does this using 
the formula of Monier, not the definition */
long trialStrongLiarCount(long n);

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

/* Since the factoredsieve stores only the smallest prime factor, the 
next routine uses that information (with access to the entire sieve 
for recursive work) to give the full factorization
Input is the sieve and a vector which will store the factors
*/
void sieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* This next only returns the distinct prime factors of n */
void distinctsieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* A sieve that returns the primes up to bound in O(bound) time.
This is a dual linear sieve of Pritchard*/
vector<long> LinearPrimeSieve(long bound);

/* returns the largest odd divisor of n */
long OddDivisor(long n);

/* returns ord_2(n), the largest power of 2 dividing n */
long Ord2(long n);

// Factor returns all the prime factors of n, stored in the given vector
// uses trial division
void trialFactor(long n, vector<long>& factors);

// Removes repeats from the factor list.  Assume here that factors is sorted
vector<long> distinctFactor(vector<long>& factors);

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(long a, long n);


// Below are functions not implemented yet.
/* returns the number of Fermat liars of n.  It does this using 
the formula of Monier, not the definition */
long FermatLiarCount(long n);
// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);

#endif  //FORMULAS_H
