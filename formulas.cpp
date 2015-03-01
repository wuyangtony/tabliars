#include "formulas.h"

NTL_CLIENT

/* Finds the smallest composite integer N such that a is a liar for N */ 
ZZ FirstNLiarRandom(ZZ a);

/* Finds the smallest composite integer N such that a is a liar for N 
Instead of using a probabilistic primality test, checks primality with 
a factored sieve */
ZZ FirstNLiarFactored(ZZ a, vector<long> &factors);

/* returns the number of strong liars of n, using the definition, 
given by an NTL implementation */
ZZ StrongLiarCount(ZZ n);
  ZZ liarcount = to_ZZ(0); 
  ZZ a = to_ZZ(a);

/* returns the number of Strong liars of n.  It does this using 
the formula of Monier, not the definition */
long trialStrongLiarCount(long n){
  cout << "this function not implemented yet\n";
return 0;
}

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
long BasicSieve(long x, RR sievebound){
	vector<long> sieve;
	sieve.reserve(x);
	for(int i=0; i<x; i++){
		sieve.at(i) = 1;
	}		
	for(int j=0; j<x; j++){
		cout << sieve[j] << " ";
	}
}

/*
This uses a sieve of Erasthothenes to factor all integers up to n
Specifically, a vector is returned that in position i contains the smallest 
prime factor of i.
*/
vector<long> FactoredSieve(long x){
  // initialize output vector so that position n contains n
  vector<long> ints;
  ints.reserve(x+1);
  for(long i = 0; i < x+1; i++){
    ints.push_back(i);
  }

  // Thm: if n composite, its smallest prime factor < sqrt(n)
  long bound = pow(x, 1.0/2);  // so we sieve up to sqrt(n)
  long prime = 2;
  while(prime <= bound){
    // for multiplies of p, set smallest prime factor to be p if 
    // a smaller prime factor wasn't already found
    for(long n = 2*prime; n <= x; n = n+prime){
      if(ints.at(n) == n) ints.at(n) = prime;
    } 
  
    // now find the next prime
    // this occurs when ints.at(n) = n
    prime++;
    while(ints.at(prime) != prime) prime++;
  }

return ints;
}

/* Since the factoredsieve stores only the largest prime factor, the 
next routine uses that information (with access to the entire sieve 
for recursive work) to give the full factorization
Input is the sieve and a vector which will store the factors
*/
void sieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* This next only returns the distinct prime factors of n */
void distinctsieveFactor(long n, vector<long>& factors, const vector<long>& sieve);

/* returns the largest odd divisor of n */
long OddDivisor(long n){
  long div;

return div;
}

/* returns ord_2(n), the largest power of 2 dividing n */
long Ord2(long n){
  long ord;

return ord;
}

// Factor returns all the distinct prime factors of n, stored in the given list
// uses trial division
// written by Steven Hayman
void trialFactor(long n, list<long>& factors);

// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(long a, long n){
  return Jacobi(to_ZZ(a), to_ZZ(n));
}


