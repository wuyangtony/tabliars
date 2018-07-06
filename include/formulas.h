#ifndef FORMULAS_H
#define FORMULAS_H
#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>
#include <cmath>
#include <exception>
NTL_CLIENT

/*
This uses a sieve of Erasthothenes to factor all integers up to n
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
@para	x:	  upper bound of the sieve
		ints: a reference to factored sieve
@return	void, but ints is passed by reference, which will be written
*/
void factoredSieve(const long& x, vector<long>& ints);

/*
Based on sieve of Erasthothenes, this will give a vector of all prime factors
of integer n, including repeats.
@para	n:		 the integer to be factored
		sieve:	 factored sieve up to n
		factors: a reference to a vector of all prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void getPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors);

/*
This does the same thing as getPrimeFactors(), with the only difference of getting
rid of all repeating prime factors.
@para	n:	 	 the integer to be factored
		sieve:	 factored sieve up to n
		factors: a reference to a vector of all distinct prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void getDistinctPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors);

/* 
This is a poly time algorithm, but currently it is a loglog factor slower 
than theoretically possible since I do not use precomputation in exp.
@para	a:	   the base number
		n:	   the modulo number
		sieve: a constant reference to a vector of factored sieve
@return	multiplicative order of a mod n
*/
long mulOrder(const long& a, const long& n, const vector<long>& sieve);

/*
This funtion finds the first generator of a multiplicative group
@para	p_power: the modulo number, a prime or prime power
		sieve:   a constant reference to a vector of factored sieve
@return	first generatort of multiplicative group mod p_power
*/
long firstGenerator(const long& p_power, const vector<long>& sieve);

/*
This finds the largest odd divisor
@para	n: the composite to be searched
@return	largeest odd divisor of n
*/
long largestOddDivisor(long n);

/*
A mirror function of largestOddDivisor()
@para	n: a positive integer
@return	the largest power of 2 that divides n
*/
long Ord2(long n);

/*
Remove repeats from a sorted list of prime factors
@para	factors: a list of prime factors, including repeats
		out:	 a reference to a vector of distinct prime factors
@return	void, but out is passed by reference, which will be written
*/
void distinctFactor(const vector<long>& factors, vector<long>& out);


/*
Returns a vector of all prime numbers up to n with O(n) runtime.
@para	n:  the upper bound of the set of prime numbers
		ps: a reference to the vector of prime numbers
@return void, but ps is passed by reference, which will be written
*/
vector<long> LinearPrimeSieve(long n);

/*
Use the formula of Monier, not the definition.
@para	n: an integer
@return	number of strong liars of n
*/
long trialStrongLiarCount(const long& n);

/*
Similar to trialStrongLiarCount, but it uses a sieving strategy which is more efficient.
@para	x: an integer
@return	number of odd integers with 2 strong liars 
*/
long sieveTwoStrongLiarsCount(const long& x);

/*
Use trial division, complexity O(sqrt(n))
@para	n: 		 an integer
		factors: a reference to the vector of prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void trialFactor(long n, vector<long>& factors);

/*
Use NTL's MillerWitness()
@para	n: an integer of type ZZ
@return	number of strong liars of n
*/
ZZ StrongLiarCount(ZZ n);

/* this is a basic sieve of Erasthothenes.  It takes integers up to 
x and sieves by primes up to sievebound, and returns the integers not sieved.
That is, the output is the number of integers up to x not divisible 
by any of the primes up to sievebound */
long BasicSieve(const long& x, RR sievebound);

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(const long& a, const long& n);


// Below are functions not implemented yet.
/* returns the number of Fermat liars of n.  It does this using 
the formula of Monier, not the definition */
long FermatLiarCount(long n);
// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);

#endif  //FORMULAS_H