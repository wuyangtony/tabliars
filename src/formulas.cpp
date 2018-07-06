// This is the final version, with format re-organized and some code optimized.
// Original author: Andrew Shallue
// Revision author: Tony Liu
// Date: Sep 18, 2017

#include "../include/formulas.h"
NTL_CLIENT

/*
This uses a sieve of Erasthothenes to factor all integers up to n.
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
@para	x:	  upper bound of the sieve
		ints: a reference to factored sieve
@return	void, but ints is passed by reference, which will be written
*/
void factoredSieve(const long& x, vector<long>& sieve)
{
	// Allocate memory for ints first
	sieve.reserve(x+1);
	// Initialize ints with values identical to respective indices
	for (long i=0; i<x+1; sieve.push_back(i++));
	// Thm: if x composite, its smallest prime factor < sqrt(x)
	const long bound = sqrt(x);
	// Start with the first prime number 2
	long p = 2;
	// For multiples of p, set smalles prime factor to be p if smaller factor not found yet
	while (p <= bound)
	{
		for (long n=2*p; n<=x; n+=p) if (sieve.at(n) == n) sieve.at(n) = p;
		// now find next prime, which occur when ints.at(n) = n
		do
		{	// p has to be incremented at least once
			++p;
		}
		while (sieve.at(p) != p);
	}
}

/*
Based on sieve of Erasthothenes, this will give a vector of all prime factors
of integer n, including repeats.
@para	n:		 the integer to be factored
		sieve:	 factored sieve up to n
		factors: a reference to a vector of all prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void getPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors)
{
	// n has to be greater than 1
	if (n <= 1) throw invalid_argument("Parameter n needs to be greater than 1.");
	// Done when cofactor reaches 1
	while (n != 1)
	{
		// add smallest prime factor to factors
		factors.push_back(sieve.at(n));
		// update cofactor
		n /= sieve.at(n);
	}
}

/*
This does the same thing as getPrimeFactors(), with the only difference of getting
rid of all repeating prime factors.
@para	n:	 	 the integer to be factored
		sieve:	 factored sieve up to n
		factors: a reference to a vector of all distinct prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void getDistinctPrimeFactors(long n, const vector<long>& sieve, vector<long>& factors)
{
	// n has to be greater than 1
	if (n <= 1) throw invalid_argument("Parameter n needs to be greater than 1.");
	// Base case 1: n = 1
	if (n == 1) return;
	// Since n != 1, add smallest prime factor of n to factors first
	factors.push_back(sieve.at(n));
	// For retrieving values
	long prime;
	// Similar process as in last function
	while (n != 1)
	{
		// get next prime factor
		prime = sieve.at(n);
		// update cofactor first this time
		n /= prime;
		// add prime only if it's not in factors
		if (factors.back() != prime) factors.push_back(prime);
	}
}

/* 
This is a poly time algorithm, but currently it is a loglog factor slower 
than theoretically possible since I do not use precomputation in exp.
@para	a:	   the base number
		n:	   the modulo number
		sieve: a constant reference to a vector of factored sieve
@return	multiplicative order of a mod n
*/
long mulOrder(const long& a, const long& n, const vector<long>& sieve)
{
	// a has to be a unit of mod n group
	if (GCD(a, n) != 1) throw invalid_argument("a needs to be a unit of mod n group.");
	// n cannot be greater than the size of sieve
	if (n > sieve.size()) throw out_of_range("n needs to be smaller than the size of sieve.");
	// Compute phi(n) using factorization of n
	long phi = 1;
	vector<long> factors;
	getPrimeFactors(n, sieve, factors);
	// Find next prime power dividing n
	long prime = factors.at(0);
	long exp = 1;
	for (long i=1; i<factors.size(); ++i)
	{
		if (factors.at(i) == prime) ++exp;
		else
		{
			// use NTL's built-in function to get prime^(exp-1)
			phi *= power_long(prime, exp-1) * (prime-1);
			prime = factors.at(i);
			exp = 1;
		}
	}
	// Get last prime power dividing n
	phi = phi * power_long(prime, exp-1) * (prime-1);
	// Reuse factors to save memory
	factors.clear();
	// Get distinct prime factors of phi(n)
	getDistinctPrimeFactors(phi, sieve, factors);
	// Build up per prime dividing phi
	long order = 1;
	// e will be phi(n) with all p factors removed
	long p, e;
	// ai will equal a^e mod n, then raised to p powers
	long ai;
	// Store power of p that divides order
	long orderfactor;
	for (long i=0; i<factors.size(); ++i)
	{
		// identify largest power of p dividing phi
		p = factors.at(i);
		e = phi;
		while (e % p == 0) e = e / p;
		// use NTL's built-in function PowerMod()
		// take (a^e)^p until congruent to 1 mod n
		ai = PowerMod(a, e, n);
		orderfactor = 1;
		while (ai != 1)
		{
			ai = PowerMod(ai, p, n);
			orderfactor *= p;
		}
		// ai^orderfactor = 1 mod n, so multiply order my orderfactor
		order *= orderfactor;
	}
	return order;
}

/*
This funtion finds the first generator of a multiplicative group
@para	p_power: the modulo number, a prime or prime power
		sieve:   a constant reference to a vector of factored sieve
@return	first generatort of multiplicative group mod p_power
*/
long firstGenerator(const long& p_power, const vector<long>& sieve)
{
	// Thm: g is generator iff mul ord of g mod p_power
	//		is equal to (p-1)*p_power/p = p_power - p_power/p
	long q = p_power - p_power / sieve.at(p_power);
	// Test each potential candidate, starting from 2
	long g = 2;
	// Denote whether the generator is found
	bool found = false;
	// For retrieving multiplicative orders
	long order;
	// Check all candidate up to p_power
	while (!found && g < p_power)
	{
		order = mulOrder(g, p_power, sieve);
		if (order == q) found = true;
		else ++g;
	}
	return g;
}

/*
This finds the largest odd divisor
@para	n: the composite to be searched
@return	largeest odd divisor of n
*/
long largestOddDivisor(long n)
{
	// Keep split in half until becoming odd
	while (n%2 == 0)
	{
		n /= 2;
	}
	return n;
}

/*
A mirror function of largestOddDivisor()
@para	n: a positive integer
@return	the largest power of 2 that divides n
*/
long Ord2(long n)
{
	// Defalt power is 0
	long p = 0;
	// Each time n divided by 2, add 1 to p
	while (n%2 == 0)
	{
		++p;
		n /= 2;
	}
	return p;
}

/*
Remove repeats from a sorted list of prime factors.
@para	factors: a list of prime factors, including repeats
		out:	 a reference to a vector of distinct prime factors
@return	void, but out is passed by reference, which will be written
*/
void distinctFactor(const vector<long>& factors, vector<long>& out)
{
	// For storing repeating factor
	long repeat = 0;
	// For retrieving each item in factors
	long factor;
	// Loop and keep updating repeat
	for (long i=0; i<factors.size(); ++i)
	{
		factor = factors.at(i);
		// Each factor can only be added to out once
		if (factor != repeat)
		{
			out.push_back(factor);
			repeat = factor;
		}
	}
}

/*
Returns a vector of all prime numbers up to n with O(n) runtime.
@para	n:  the upper bound of the set of prime numbers
		ps: a reference to the vector of prime numbers
@return void, but ps is passed by reference, which will be written
*/
void LinearPrimeSieve(const long& n, vector<long>& ps)
{
	// Get sqrt(n) first
	const long bound = sqrt(n);
	// An array to denote primality
	vector<long> ints;
	ints.reserve(n+1);
	// Set of primes up to sqrt(n)
	vector<long> shps;
	// Index of current prime
	long ip;
	// For while loop
	bool done;
	// Get a factored sieve up to bound
	vector<long> factors;
	factoredSieve(bound, factors);
	// Use factors to store all prime number up to bound
	for (long i=2; i<factors.size(); ++i) if (factors.at(i) == i) shps.push_back(i);
	// Initialize ints with all 1's
	for (long i=0; i<=n; ++i) ints.push_back(1);
	// Main loop start from here
	// Loop over f, then p works since uniquely n = pf with
	// gcd(q, f) = 1 for q < p
	for (long f=2; f<n/2; ++f)
	{
		// Start at p = 2
		ip = 0;
		done = false;
		while (!done)
		{
			// cross off n = pf
			ints.at(shps.at(ip) * f) = 0;
			// done if p|f or next prime makes pf too large
			if (f % shps.at(ip) == 0)
			{
				done = true;
			}
			else
			{
				++ip;
				if (shps.at(ip) * f > n) done = true;
			}
		}
	}
	// Finally push all prime numbers to ps
	for (long i=2; i<=n; ++i)
	{
		if (ints.at(i) == 1) ps.push_back(i);
	}
}

/*
Use the formula of Monier, not the definition.
@para	n: an integer
@return	number of strong liars of n
*/
long trialStrongLiarCount(const long& n)
{
	// n needs to be odd

	long liarcount = 0;
	// Factor n using trial division
	vector<long> f;
	trialFactor(n, f);
	// Remove repeats from f
	vector<long> factors;
	distinctFactor(f, factors);
	// Compute product of gcd(n', p') and smallest ord_2(p-1)
	long gcdprod = 1;
	long minord = Ord2(factors.at(0)-1);
	long tempord;
	for (long i=0; i<factors.size(); ++i)
	{
		gcdprod *= GCD(largestOddDivisor(n-1), largestOddDivisor(factors.at(i)-1));
		tempord = Ord2(factors.at(i)-1);
		if (tempord < minord) minord = tempord;
	}
}

/* Similar to trialStrongLiarCount, but it uses a sieving strategy which is more efficient.
@para	x: an integer
@return	number of odd integers with 2 strong liars 
*/
long sieveTwoStrongLiarsCount(const long& x)
{
	long liarcount = 0;
	// Have a factroed sieve
	vector<long> sieve;
	sieve.reserve(x+1);
	factoredSieve(x, sieve);
	// Store prime factors of x
	vector<long> factors;
	// Store which case we are in for each number
 	vector<long> cases;
 	cases.reserve(x+1);
 	// Initialize to cases storing 2 for each odd entry, 0 for each even,
 	// ultimately 1 will mean that odd number has two strong liars
 	for (long i=0; i<x+1; ++i)
 	{
 		if (i%2 == 0) cases.push_back(0);
 		else cases.push_back(2);
 	}
 	// 1 is not a composite with 2 strong liars
 	cases.at(1) = 0;
 	// now, for all primes p <= x, all odd prime r|(p-1), 
 	// cross off n = p mod (pr), since for these r | gcd(n', p')
 	// we can start at p=3 since p=2 has no odd primes dividing p-1
 	long r, index;
 	for (long p=3; p<sieve.size(); ++p)
 	{
 		if (sieve.at(p) == p) // p is prime
 		{
 			cases.at(p) = 0; // primes are not composite
 			getDistinctPrimeFactors(p-1, factors, sieve);
 			for (long j=0; j<factors.size(); ++j)
 			{
 				r = factors.at(j);
 				// only keep r if it's odd
 				if (r%2 != 0)
 				{
 					index = p;
 					// cross off n = p mod (pr)
 					while (index < x+1)
 					{
 						cases.at(index) = 0;
 						index += p * r;
 					}
 				}
 			}
 		}
 	}
 	// Make sure the remaining composites have a factor = 3 (4)
 	for (long p=3; p<sieve.size(); ++p)
 	{
 		if (sieve.at(p)==p && p%4==3)
 		{
 			index = p;
 			while (index < x+1)
 			{
 				if (cases.at(index) == 2) cases.at(index) = 1;
 				index += p;
 			}
 		}
 	}
 	// Count the number of strong liars
 	for (long i=0; i<cases.size(); ++i)
 	{
 		if (cases.at(i) == 1) ++liarcount; 
 	}
 	return liarcount;
}

/*
Use trial division, complexity O(sqrt(n))
@para	n: 		 an integer
		factors: a reference to the vector of prime factors of n
@return	void, but factors is passed by reference, which will be written
*/
void trialFactor(long n, vector<long>& factors)
{
	while (n != 1)
	{
		long primefinder = 2;
		// keep increasing the prime until it is a divisor
		// first found must be prime, stop at sqrt of the cofactor
		while (n%primefinder != 0 && primefinder*primefinder < n) ++primefinder;
		// if primefinder divides n, add prime to list and continue
		if (n%primefinder == 0)
		{
			factors.push_back(primefinder);
			n /= primefinder;
		}
		else // in this case, the cofactor is prime
		{
			factors.push_back(n);
			n = 1;
		}
	}
}

/*
Use NTL's MillerWitness()
@para	n: an integer of type ZZ
@return	number of strong liars of n
*/
ZZ StrongLiarCount(ZZ n)
{
	// Input needs to be odd

	ZZ liarcount = to_ZZ(0);
	// Test each potential witness
	for (ZZ i = to_ZZ(1); i<n; ++i)
	{
		if (MillerWitness(n, i) == 0) ++liarcount;
	}
	return liarcount;
}

/* this is a basic sieve of Erasthothenes.  It takes integers up to 
x and sieves by primes up to sievebound, and returns the integers not sieved.
That is, the output is the number of integers up to x not divisible 
by any of the primes up to sievebound */
long BasicSieve(const long& x, RR sievebound)
{
	vector<long> sieve;
	sieve.reserve(x);
	for(int i=0; i<x; i++)
	{
		sieve.at(i) = 1;
	}   
	for(int j=0; j<x; j++)
	{
		cout << sieve[j] << " ";
	}
}

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(const long& a, const long& n)
{
	return Jacobi(to_ZZ(a), to_ZZ(n));
}