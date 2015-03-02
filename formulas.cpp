#include "formulas.h"

NTL_CLIENT

/* Finds the smallest composite integer N such that a is a liar for N */ 
ZZ FirstNLiarRandom(ZZ a);

/* Finds the smallest composite integer N such that a is a liar for N 
Instead of using a probabilistic primality test, checks primality with 
a factored sieve */
ZZ FirstNLiarFactored(ZZ a, vector<long> &factors);

/* returns the number of strong liars of n, using NTL MillerWitness*/
ZZ StrongLiarCount(ZZ n){
  if(n % 2 == 0) cout << "Error in StrongLiarCount: input needs to be odd\n";
  ZZ liarcount = to_ZZ(0); 
  // now test each potential witness
  for(ZZ i = to_ZZ(1); i < n; i++){
    if(MillerWitness(n, i) == 0){ //MillerWitness returns 1 if i witness
      liarcount++;
    }
  }
return liarcount;
}

/* returns the number of Strong liars of n.  It does this using 
the formula of Monier, not the definition */
long trialStrongLiarCount(long n){
  if(n % 2 == 0) cout << "Error in trialStrongLiarCount: input needs to be odd\n";
  // first task is to factor n.  We do this using trial division
  vector<long> factors;
  trialFactor(n, factors);
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

/* Since the factoredsieve stores only the smallest prime factor, the 
next routine uses that information (with access to the entire sieve 
for recursive work) to give the full factorization
Input is the sieve and a vector which will store the factors
*/
void sieveFactor(long n, vector<long>& factors, const vector<long>& sieve){
  while(n != 1){ // we're done when the cofactor reaches 1
    long prime = sieve.at(n);  // gives smallest prime factor
    factors.push_back(prime);  // add it to the list of factors
    n = n / prime;  // update cofactor
  }
return;
}

/* This next only returns the distinct prime factors of n */
void distinctsieveFactor(long n, vector<long>& factors, const vector<long>& sieve){
  // conveniently, in sieveFactor the primes are listed in order from 
  // smallest to largest, with repeated factors adjacent.  We can exploit this
  while(n != 1){
    long prime = sieve.at(n); // gives next prime
    n = n / prime;  // update cofactor
    // if prime already appears at end of factors, don't add it
    if(factors.back() != prime) factors.push_back(prime);
  }
return;
}

/* returns the largest odd divisor of n */
long OddDivisor(long n){
  long div = n; // if n odd then that is what is returned
  while(div % 2 == 0){ // while n still even, keep dividing by 2
    div = div / 2;
  }
return div;
}

/* returns ord_2(n), the largest power of 2 dividing n */
long Ord2(long n){
  long ord = 0;
  while(n % 2 == 0){  // keep dividing n by 2 and adding 1 to ord
    ord++;
    n = n / 2;
  }

return ord;
}

// Factor returns all the  prime factors of n, stored in the given vector
// uses trial division, complexity O(sqrt(n))
void trialFactor(long n, vector<long>& factors){
  while(n != 1){ // still work to do if non-trivial cofactor
    long primefinder = 2;
    // keep increasing the prime until it is a divisor.  
    // First found must be prime, stop at sqrt of the cofactor
    while(n % primefinder != 0 && primefinder < floor(sqrt(n))) primefinder++;  
    // if primefinder divides n, add prime to list and continue
    if(n % primefinder == 0){
      factors.push_back(primefinder); // add to list
      n = n / primefinder;  // update cofactor
    }else{  // in this case the cofactor is prime
      factors.push_back(n);
      n = n / n;
    }
  }    
return;
}

/* distincttrialFactor is same as trial factor, except only distinct prime 
factors of n are returned.  Exploits that
*/ 

// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(long a, long n){
  return Jacobi(to_ZZ(a), to_ZZ(n));
}


