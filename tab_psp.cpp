#include "tab_psp.h"

NTL_CLIENT


/* Uses NTL's MillerWitness to return the strong pseudoprimes to the base 
a.  Note that ProblPrime used to test compositeness, so might make mistakes*/
vector<ZZ> TrivialStrongTab(ZZ a, ZZ bound){
  vector<ZZ> psps; // will hold the pseudoprimes found

  //n is a psp if it is odd, composite, and a not a Miller Witness
  //note base is a%n, since MillerWitness requires a < n
  //also note: if a % n = 0, a neither a witness nor a liar, so I don't 
  //say that n is a pseudoprime in this case
  for(ZZ n = conv<ZZ>(3); n <= bound; n = n+2){
    if(a % n != 0){
    if(!ProbPrime(n) && !MillerWitness(n, a%n)){
      psps.push_back(n);
    }
  }
  }
return psps;
}

/* Same goal, but now use original algorithm in the paper with 
an O(n loglog n) complexity.  So no fancy sieve techniques
Output: ints will be modified so that 1 at index i means i is a strong 
pseudoprime to the base a.  Requires a factored sieve.

Note frequency of bound+1.  Want to include the number equal to bound.
*/
void SieveStrongTab(long a, long bound, vector<long>& ints, vector<long>& factoredsieve){
  // bound should be valid for the factored sieve
  if(bound+1 != factoredsieve.size()){
    cout << "Error in SieveStrongTab: bound does not match size of factoredsieve\n";
    cout << "bound = " << bound << " vs sieve size = " << factoredsieve.size() << "\n";
    return;
  }
 
  // first initialize integers vector to have correct size, start as all 1's
  ints.clear();
  ints.reserve(bound+1); //include bound as a number checked
  for(long i = 0; i <= bound; i++){
    ints.push_back(1);
  }
  // except that 0,1 are not pseudoprimes
  ints.at(0) = 0; ints.at(1) = 0;
  // we also need an array to store power of 2 dividing order of a
  vector<long> TwoPower;
  TwoPower.reserve(bound+1);
  for(long i = 0; i <= bound; i++){
    TwoPower.push_back(-1);
  }

  long q; // for prime powers
  long ord_aq; // stores mul order of a modulo q
  long twopower; // power of 2 dividing ord_aq
  long n;   // integers in the array to be crossed off

  // can't apply miller-rabin test to even ints, so cross them off
  n = 2;
  while(n <= bound){
    ints.at(n) = 0;
    n = n+2;
  }

  // now there is a big loop over prime powers
  for(long p = 3; p <= bound; p++){

    if(factoredsieve.at(p) == p){ // smallest factor of p is p => p prime
    
      ints.at(p) = 0;  // primes are not pseudoprimes
      q = p;  // q is a prime power
    
      //if gcd(a,q) != 1, no multiples of q are a pseudoprimes
      if( a % p == 0){
        n = q;
        while(n <= bound){
          ints.at(n) = 0;
          n = n + q;
        }
      }
      else while(q <= bound){
        ord_aq = MulOrder(a, q, factoredsieve); //mult order of a mod q  
        twopower = Ord2(ord_aq);  // the power of 2 dividing that order
      
        //loop over multiples n of q prime, updating TwoPower array
        n = q;
        if(factoredsieve.at(q) == q){ //only update for q prime
          while(n <= bound){

            // if value is -1, we haven't seen a prime dividing n yet
            if(TwoPower.at(n) == -1) TwoPower.at(n) = twopower;
            //To be strong psp, need 2power equal for all primes dividing n
            else if(TwoPower.at(n) != twopower) ints.at(n) = 0;
            n = n+q;
          } // end while TwoPower loop 
        }

        // strong psp require ord_a(q) | p-1 for all p | n
        if( (p-1) % ord_aq != 0){
          n = q;
          while(n <= bound){
            ints.at(n) = 0;
            n = n + q;
          }
        } //end if ord_aq not | p-1
        else{ // need to keep n = q mod q * ord_aq, cross off others
          n = q;
          while(n <= bound){

            // note the special case: if ord_aq = 1 then all multiples 
            // of q should not be crossed off
            if(n % (q * ord_aq) != q && ord_aq != 1) ints.at(n) = 0;
            n = n + q;
          }
        }// end else ord_aq | p-1
        q = q * p;
      } // end while on prime powers
    } // end if p prime
  } //end big for loop
return;
}

/* Same goal, but now the Sieve takes linear time ( O(n) ) by 
touching each composite only once */
void LinearSieveStrongTab(long a, long bound, vector<long>& ints, vector<long>& factoredsieve){

return;
}

/* Tests Fermat condition by simply powering, and ProbPrime for primality.
returns a vector containing all a-Fermat psp up to and including bound */
vector<ZZ> TrivialFermatTab(ZZ a, ZZ bound){
  vector<ZZ> psps; // will hold the pseudoprimes found
  ZZ base;  // will hold a%n

  //n is a psp if it is composite and a^{n-1} = 1 mod n
  //note base is a%n, since we are working modulo n anyway
  //also note: if a % n = 0, a neither witness nor liar, so I don't 
  //say that n is a pseudoprime in this case
  for(ZZ n = conv<ZZ>(2); n <= bound; n++){
    base = a % n;
    if(base != 0){
    if(!ProbPrime(n) && PowerMod(base, n-1, n) == 1){
      psps.push_back(n);
    }
  }
  }
return psps;
}


