#include "../include/first_liar.h"

NTL_CLIENT

/* Finds the smallest composite integer N such that a is a liar for N 
  Uses NTL's MillerWitness, and ProbPrime to test compositeness 
  We will restrict ourselves to searching for odd integers N > a

  Testing of MillerWitness:  n has to be odd, positive
  MillerWitness(9,0) = 0, MillerWitness(9,3) = 1
*/
ZZ FirstSpspRandom(ZZ a){
  // first n checked is the first odd integer n > a
  // we'll be adding two at the start of the while loop
  ZZ firstpsp = a;
  if(a % 2 == 0) firstpsp--;
  
  bool done = false;

  while(!done){
    firstpsp = firstpsp + 2;
    
    // done if n is composite and a is not a witness for its compositeness
    if(!ProbPrime(firstpsp) && !MillerWitness(firstpsp, a)) done = true;
  }
return firstpsp;
}

/* Finds the smallest odd composite integer N such that a is a liar for N 
Instead of using a probabilistic primality test, checks primality with 
a factored sieve 
  Here we do allow N < a, though N = 0 mod a are neither witnesses nor liars
*/
long FirstSpspFactored(ZZ a, vector<long> &factors){
  long n = 7; // 9 is the first odd composite integer, will add two in while loop
  ZZ a_red; // we will be reducing a % n so that 1 <= a < n
  bool done = false;

  // now check all odd n until find one that is odd and strong psp
  while(!done){
    n = n + 2; // only check odd n
    a_red = a % n;  // reduce a
  
    // if a % n = 0, neither liar nor witness. MillerWitness calls it a liar
    if(a_red != 0){
      // if not prime and a not a witness we have found the n we want
      if(factors.at(n) != n && !MillerWitness(to_ZZ(n), a_red) ) done = true;
    }
  }
return n;
}

