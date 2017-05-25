#include "formulas.h"

NTL_CLIENT



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
  long liarcount = 0;

  // first task is to factor n.  We do this using trial division
  vector<long> factors;
  trialFactor(n, factors);
  factors = distinctFactor(factors); // remove repeated primes

  // compute the product of gcd(n', p') and smallest ord_2(p-1)
  long gcdproduct = 1;
  long minord = Ord2(factors.at(0)-1); // for smallest ord_2(p-1)
  long tempord;
  for(long i = 0; i < factors.size(); i++){
    gcdproduct = gcdproduct * GCD(OddDivisor(n-1), OddDivisor(factors.at(i) - 1));
    tempord = Ord2(factors.at(i)-1);
    if(tempord < minord) minord = tempord;
  }

  // now, the number of strong liars is gcdproduct * (1 + (2^(rv)-1)/(2^r-1))
  liarcount = gcdproduct * (1 + (power_long(2, factors.size() * minord)-1) / (power_long(2, factors.size()) - 1) );

return liarcount;
}


/* Similar to trialStrongLiarCount, but uses a 
sieving strategy which is more efficient.  Uses FactoredSieve
and sieveFactor below
Specifically, output is number of odd composite integers with 2 strong liars 
*/
long  sieveTwoStrongLiarsCount(long x){
  long liarcount = 0;
  // the sieve stores the smallest prime factor of i in position i
  vector<long> sieve = FactoredSieve(x);
  vector<long> factors; // for storing prime factorizations

  // but we need another vector that stores which case we are in
  // initialize to cases storing 2 for each odd entry, 0 for each even
  // ultimately 1 will mean that odd number has two strong liars
  vector<long> cases;
  cases.reserve(x+1);
  long i = 0;
  while(i < x+1){ //x+1 so we get integers up to including x, plus 0
    if(i % 2 == 0) cases.push_back(0);
    else cases.push_back(2);
    i++;
  }
  cases.at(1) = 0; // 1 is not a composite with two strong liars

  // now, for all primes p <= x, all odd prime r|(p-1), 
  // cross off n = p mod (pr), since for these r | gcd(n', p')
  // we can start at p=3 since p=2 has no odd primes dividing p-1
  long r;
  long index;
  for(long p = 3; p < sieve.size(); p++){
    if(sieve.at(p) == p){ // then p is prime
      cases.at(p) = 0; // primes are not composites with two strong liars
      distinctsieveFactor(p-1, factors, sieve);

      for(long j = 0; j < factors.size(); j++){
        r = factors.at(j);
        if(r % 2 != 0){ // only keep r if it is odd
          index = p;

          while(index < x+1){ // now cross off n = p mod (pr)
            cases.at(index) = 0;
            index = index + p*r;
          } // end while
        } // end if r odd
      } // end for factors
    } // end if prime
  } // end for p

  // next we need to ensure that the remaining composites have a factor = 3 (4)
  for(long p = 3; p < sieve.size(); p++){
    if(sieve.at(p) == p && p%4 == 3){
      index = p;
      while(index < x+1){
        if(cases.at(index) == 2) cases.at(index) = 1;
        index = index + p;
      }
    } // end if p = 3 (4)
  } // end for p

  // finally, we count up the liars
  for(long i = 0; i < cases.size(); i++){
    if(cases.at(i) == 1) liarcount++;
  }

return liarcount;
}

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
This uses a sieve of Erasthothenes to factor all integers up to x
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

/*
 * Find the first generator of the multiplicative group mod p, given p
 * as any prime power
 * Input   1)p_power: a long integer representing a prime power
 * Output: the first number that generates the mult group
*/
long firstGenerator(long p_power) {
  // need to use list of all sieve factors
  vector<long> sieve = FactoredSieve(p_power);
  // Thm: g is a generator iff mult order of g mod p_power
  //      is equal to p_power(p-1)/p = p_power - p_power/p
  long q = p_power - p_power / sieve[p_power];
  // test each potential canditate, starting from 2
  long g = 2;
  // indicate whether generator found
  bool found = false;
  // As long as generator not found and cadidate smaller
  // than the prime power, keep checking
  while (!found && g < p_power) {
    // get MulOrder(g, p_power)
    long order = MulOrder(g, p_power, sieve);
    if (order == q) {
      found = true;
    }
    else {
      g++;
    }
  }
  return g;
}

/* Since the factoredsieve stores only the smallest prime factor, the 
next routine uses that information (with access to the entire sieve 
for recursive work) to give the full factorization
Input is the sieve and a vector which will store the factors
*/
void sieveFactor(long n, vector<long>& factors, const vector<long>& sieve){
  factors.clear(); // make sure the factors vector is empty
  while(n != 1){ // we're done when the cofactor reaches 1
    long prime = sieve.at(n);  // gives smallest prime factor
    factors.push_back(prime);  // add it to the list of factors
    n = n / prime;  // update cofactor
  }
return;
}

/* This next only returns the distinct prime factors of n */
void distinctsieveFactor(long n, vector<long>& factors, const vector<long>& sieve){
  factors.clear(); // make sure the factors vector is empty
  // conveniently, in sieveFactor the primes are listed in order from 
  // smallest to largest, with repeated factors adjacent.  We can exploit this
  while(n != 1){
    long prime = sieve.at(n); // gives next prime
    n = n / prime;  // update cofactor
    // if prime already appears at end of factors, don't add it
    if(factors.size() == 0) factors.push_back(prime);
    else if(factors.back() != prime){
      factors.push_back(prime);
    }
  }
return;
}

/* A sieve that returns the primes up to bound in O(bound) time.
This is a dual linear sieve of Pritchard*/
vector<long> LinearPrimeSieve(long bound){
  vector<long> primes; // the output
  vector<long> ints; // the array to be sieved
  vector<long> shortprimes; // primes up to sqrt(bound) using basic sieve
  long ip;  // index of the current prime
  bool done; // for while loop

  // we need to know what sqrt(bound) is
  long sqrtbound = floor(sqrt(bound));
  // first, we need the primes up to \sqrt(bound);
  vector<long> factors = FactoredSieve(sqrtbound);
  // factoredsieve returns smallest factor of i, so prime if this is i
  for(long i = 0; i < factors.size(); i++){
    if(factors.at(i) == i && i > 1) shortprimes.push_back(i);
  }

  // now itialize ints with all 1's (though 0,1 not prime)
  for(long i = 0; i <= bound; i++) ints.push_back(1);
  ints.at(0) = 0;  ints.at(1) = 0;

  // main loop.  Dual, so we loop over f, then p
  // works since n uniquely written as n = pf with gcd(q,f)=1 for q < p
  for(long f = 2; f < bound / 2; f++){
    ip = 0; // start at p = 2
    done = false;
    while(!done){
      // cross off n = p*f
      ints.at(shortprimes.at(ip) * f) = 0;

      // done if p | f or next prime makes pf too big
      if(f % shortprimes.at(ip) == 0){
        done = true;
      }else{
        ip++;
        if(shortprimes.at(ip)*f > bound) done = true; 
      }
    } // end while over primes
  } // end for main loop

  // finally, push the primes onto the output vector and return it.
  for(long i = 0; i < ints.size(); i++){
    if(ints.at(i) == 1) primes.push_back(i); 
  }
return primes;
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

/* returns multiplicative order of a modulo n
prints to cout an error if a is not a unit.  Input includes factored sieve.
This is a poly time algorithm 
*/
long MulOrder(long a, long n, vector<long>& factoredsieve){
  // first check that a unit and that n fits into the sieve
  if( GCD(a,n) != 1){ 
    //cout << "Error in MulOrder: a = " << a << " not a unit of " << n << endl;
    return 0;
  }
  if(n >= factoredsieve.size()){ 
    //cout << "Error in MulOrder: " << n << "is bigger than the size of the factored sieve\n";
    return 0;
  }

  // next we need to compute phi(n).  We'll do this using factorization of n
  long phi = 1;
  vector<long> n_primes;
  sieveFactor(n, n_primes, factoredsieve);

  // now find the next prime power dividing n, and multiply phi by correct term
  long index = 0;
  long prime = n_primes.at(index);
  long exp = 1;
  index++;
  while(index < n_primes.size()){
    if(n_primes.at(index) == prime){
      index++;
      exp++; // in this case, have another instance of prime
    }    
    else{
      // phi = phi * p^(e-1) * (p-1)
      phi = phi * power_long(prime, exp-1) * (prime - 1);

      // new prime, reset exp and increment index
      prime = n_primes.at(index);
      exp = 1;
      index++; 
    } 
  } // end while
  // catch the last prime power dividing n
  phi = phi * power_long(prime, exp-1) * (prime-1);

  // Now, I need the distinct factors of phi(n)
  vector<long> phi_primes;
  distinctsieveFactor(phi, phi_primes, factoredsieve);
  
  long order = 1;  // we'll build up per prime dividing phi
  long p, e;  // e will be phi(n) with all p factors removed
  long ai;  // ai will equal a^e mod n, then raised to p powers
  long orderfactor;  //will be power of p that divides order
  for(long i = 0; i < phi_primes.size(); i++){

    // identify the largest power of p that divides phi
    p = phi_primes.at(i);
    e = phi;
    while(e % p == 0) e = e / p;

    // now take (a^e)^p until we get identity mod n
    ai = PowerMod(a, e, n);
    orderfactor = 1;
    while(ai != 1){
      ai = PowerMod(ai, p, n);
      orderfactor = orderfactor * p;
    }
    // ai^{orderfactor} = 1 mod n, so multiply order my orderfactor
    order = order * orderfactor;

  } // end for
return order;

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

// Removes repeats from the factor list.  Assume here that factors is sorted
vector<long> distinctFactor(vector<long>& factors){
  vector<long> output;
  long value = 0; // for storing the current value seen
  long factor;  // for storing each element of factors in turn.  

  // now loop through factors, looking for new values
  for(long i = 0; i < factors.size(); i++){
    factor = factors.at(i);
    if(factor != value){ // if it does match value, no action taken
      output.push_back(factor); // if new value, push it onto output
      value = factor;  // and update value
    }
  }
return output;
}

// this is a place holder.  For now it is implemented as NTL Jacobi(a,n)
long slow_jacobi(long a, long n){
  return Jacobi(to_ZZ(a), to_ZZ(n));
}


// ***************************************************************
// Below are the functions that have not been implemented hitherto

/* returns the number of Fermat liars of n.  It does this using 
the formula of Monier, not the definition */
long FermatLiarCount(long n);

// if m has a factor store it in f and return 1, otherwise return 0
// helper function for Factor, written by Steven Hayman
long findFactor(long& m, long& f);


