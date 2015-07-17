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

/* A linear sieve technique for tabulating Fermat pseudoprimes.
Uses the DoubleLinkedListArray for contast time deletions

NOTE!!!  Does not work!  In fact, whole idea might be flawed.  See README
*/
vector<long> LinearSieveFermatTab(long a, long bound, vector<long>& factoredsieve){
  // first, set up the linked list
  DoubleLinkedListArray storage = DoubleLinkedListArray(bound+1);
  storage.remove(0); storage.remove(1); // 0,1 not pseudoprimes
 
  // other needed variables
  long p; // the prime in the prime power
  long q; // for the prime power
  long f; // element of F(q)
  long order; // mult order of a modulo q

  // need to cross of n for each prime power
  for(long p = 2; p < bound; p++){
    if(factoredsieve.at(p) == p){ // then p is prime
      q = p;
      //storage.remove(p); // primes not pseudoprimes
      while(2*q <= bound){

        //testing
        cout << "q = " << q << "\n";
          for(long i=0; i < bound; i++){
            if(storage.at(i).ison()) cout << i << " ";
          }
          cout << "\n";
        

        // find the largest element of F(q)
        // warning: starting at 2 will probably spoil the complexity, 
        // but I don't know how to find the smallest element
        f = 2; 
        // when next is negative, that signifies the end of the list
        // also stop if q*f is bigger than bound
        while(storage.at(f).getnext() >= 0 && q*storage.at(f).getnext() <= bound){
          cout << "f: " << f << " next f: " << storage.at(f).getnext() << " "; 
          f = storage.at(f).getnext();
        }
        //testing
        cout << "largest f = " << f << "\n";

        // now remove qf for f in F(q)
        // i.e. remove if gcd(a,q) != 1 or order nmid p-1 or f != 1 mod order
        // Note that f should be relatively prime to p
        while(f > 0){ //f=-1 means fallen off left end of the list
          if(f % p == 0){ 
            // if a multiple of p, skip. save for different prime power
            f = storage.at(f).getprev();
          }else if( a % p == 0){ // a not a unit, so remove all multiples of q
            storage.remove(q*f);
            f = storage.at(f).getprev();
          }else{
            order = MulOrder(a, q, factoredsieve);
            if(p-1 % order != 0 && f % order != 1){ // other non psp
              storage.remove(q*f);
              f = storage.at(f).getprev();
            }else f = storage.at(f).getprev(); // if not removed, go to next f
          }
        } //end while f>0

        //check if q itself is a pseudoprime.  Warning: we're repeating work
       // if(a % p == 0 || p-1 % order != 0){
         // storage.remove(q);
       // }
        // increment the prime power
        q = q * p;
      } // end while q <= bound
    } // end if p is prime
  }// end for p

cout << "before removing primes\n";

// now remove primes and prime powers
for(long p=2; p < bound; p++){
  if(factoredsieve.at(p) == p){
    storage.remove(p);
    q = p;
    while(q < bound){
      cout << "current prime power is " << q << "\n";
      if(a % p == 0 || p-1 % order != 0){
        storage.remove(q);
      }
      q = q * p;
    }
  }
}
cout << "after removing primes\n";
// copy over pseudoprime
vector<long> pseudoprimes;
for(long i=0; i < bound+1; i++){
  if(storage.at(i).ison()) pseudoprimes.push_back(i);
}
return pseudoprimes;
}

/* Returns the set F(q) for a linear sieve strategy for tabulating Fermat psp
F(q) = {3 <= f <= n | gcd(q,f)=1, for r < q, r nmid f or f = 1 mod \ell_a(r)}
Here the input q is given as q = p^e.
Note, this is a brute force algorithm.  Not fast.
*/
vector<long> FermatSieveF(long p, long e, long n, long a){
  // factored sieve required for computing orders
  vector<long> factors = FactoredSieve(n);

  // factors of a are needed as well
  vector<long> afactors;
  trialFactor(a, afactors);

  vector<long> fs;  // for the output
  bool include;
  long primepower; // prime powers will be powers of r
  long order;

  for(long f = 2; f <= n; f++){
    if( f % p != 0){ // only want f relatively prime to p
      include = true;
      
      //only possibly include an f that shares a prime factor with a
      // if that is the smallest prime factor of a, that it is p
      if(f % afactors.at(0) == 0){
        if(afactors.at(0) == p){
          fs.push_back(f); //included in this case
          continue;
        }else continue; //not included
      }
      if(afactors.size() > 0){
        for(long j = 1; j < afactors.size(); j++){
          if(f % afactors.at(j) == 0) continue; //not included
        }
      }

      // now loop over prime powers whose prime is less than p
      for(long r = 2; r < p; r++){
        if(factors.at(r) == r && GCD(r,a)==1){ // want r prime and a unit
          primepower = r;
          while(primepower < n){
            
            order = MulOrder(a, primepower, factors);

            //f is included if for all r, r does not divide f, or f=1 (ell_a(r))
            if(f % primepower == 0 && f % order == 1) include = false;
            primepower = primepower * r;   
          } // end while primepower < n
        } // end if r prime
      } // end for r
      if(include) fs.push_back(f);
    } // end if f % p
  } // end for f

return fs;
}


