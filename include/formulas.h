#ifndef FORMULAS_H
#define FORMULAS_H
#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>
#include <cmath>
NTL_CLIENT

/*
This uses a sieve of Erasthothenes to factor all integers up to n
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
@para		x:    a constant reference to a positive integer
		ints: a reference to factored sieve
@return		void, but ints is passed by reference, which will be written
*/
void factoredSieve(const long& x, vector<long>& ints);

/*
Based on sieve of Erasthothenes, this will give a vector of all prime factors
of integer n, including repeats.
@para		n:	 a positive integer
		sieve:	 a constant reference to factored sieve up to n
		factors: a reference to a vector of all prime factors of n
@return		void, but factors is passed by reference, which will be written
*/
void getPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors);

/*
This does the same thing as getPrimeFactors(), with the only difference of getting
rid of all repeating prime factors.
@para		n:	 a positive integer
		sieve:	 a constant reference to factored sieve up to n
		factors: a reference to a vector of all prime factors of n
@return		void, but factors is passed by reference, which will be written
*/
void getDistinctPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors);

/* 
This is a poly time algorithm, but currently it is a loglog factor slower 
than theoretically possible since I do not use precomputation in exp.
@para		a: 	a constant reference to the base number
		n:	a constant reference to the modulo number
		sieve: 	a constant reference to a vector of factored sieve
@return		multiplicative order of a mod n
*/
long mulOrder(const long& a, const long& n, const vector<long>& sieve);

/*
This funtion finds the first generator of a multiplicative group
@para		p_power: a constant reference to a prime power
			sieve:   a constant reference to a vector of factored sieve
@return		the first generatort for mult group mod p_power
*/
long firstGenerator(const long& p_power, const vector<long>& sieve);

/*
Credit to Ruchir Carg, the author of this algorithm from GeeksforGeeks.com
@para		a: the number to be found inverse of
			p: the modulo
@returns	the multiplicative inverse of a mod p
*/
long inverseMod(long a, long p);

/*
This finds the largest odd divisor
@para		n: a constant reference to an integer
@return		the largeest odd divisor of n
*/
long largestOddDivisor(const long& n);

/*
This finds the largest power of 2 that divides n
@para		n: a positive integer
@return		the largest power of 2 that divides n
*/
long Ord2(long n);

/* returns the number of Strong liars of n.  It does this using 
the formula of Monier, not the definition */
long trialStrongLiarCount(long n);

/* Similar to trialStrongLiarCount, but uses a 
sieving strategy which is more efficient.  Uses FactoredSieve
and sieveFactor below
Specifically, output is number of odd integers with 2 strong liars 
*/
long  sieveTwoStrongLiarsCount(long x);

/* A sieve that returns the primes up to bound in O(bound) time.
This is a dual linear sieve of Pritchard*/
vector<long> LinearPrimeSieve(long bound);

// Factor returns all the prime factors of n, stored in the given vector
// uses trial division
void trialFactor(long n, vector<long>& factors);

// Removes repeats from the factor list.  Assume here that factors is sorted
vector<long> distinctFactor(vector<long>& factors);

/* returns the number of strong liars of n, using the definition, 
given by an NTL implementation */
ZZ StrongLiarCount(ZZ n);

/* this is a basic sieve of Erasthothenes.  It takes integers up to 
x and sieves by primes up to sievebound, and returns the integers not sieved.
That is, the output is the number of integers up to x not divisible 
by any of the primes up to sievebound */
long BasicSieve(long x, RR sievebound);

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