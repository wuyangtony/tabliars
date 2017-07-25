#include "../include/tab_liars.h"

NTL_CLIENT

/*
Tony's implementation of finding all Fermat liars using generators
*/
void tony_tabliars(const long& n, const vector<long>& sieve, vector<long>& liars)
{
  // get distince prime factors of n
  vector<long> primefactors;
  getDistinctPrimeFactors(n, sieve, primefactors);
  // get generators for each factor
  vector<long> generators;
  generators.reserve(primefactors.size());
  for (long i=0; i<primefactors.size(); ++i)
  {
    long g = firstGenerator(primefactors.at(i), sieve);
    generators.push_back(g);
  }
  // now fg stores set of (factor, generator) pairs, use CRT to get g hats
  vector<long> ghats;
  ghats.reserve(primefactors.size());
  // compute product of all prime factors
  long prod = 1;
  for (long i=0; i<primefactors.size(); ++i)
  {
    prod *= primefactors.at(i);
  }
  // Instead of having separate arrays for partial products and inverses,
  // compute the sum of their products since remainders are all 1s
  long cpsum = 0;
  // an array of complex products of partial product and its inverse
  long cp[primefactors.size()];
  for (long i=0; i<primefactors.size(); ++i)
  {
    long pp = prod / primefactors.at(i);
    long in = inverseMod(pp, primefactors.at(i));
    cp[i] = pp * in;
    cpsum += cp[i];
  }
  // ghats[i] = (cpsum + cp[i]*(generators[i]-1)) % prod
  for (long i=0; i<generators.size(); ++i)
  {
    long g = cpsum + cp[i] * (generators[i]-1);
    ghats.push_back(g%prod);
  }
  // use orders to create an Odometer
  vector<long> orders;
  orders.reserve(primefactors.size());
  // for each ghat, raise it to power d = (p-1) / gcd(n-1, p-1)
  for (long i=0; i<ghats.size(); ++i)
  {
    long power = primefactors.at(i)-1;
    long order = GCD(n-1, power);
    orders.push_back(order);
    power = power / GCD(n-1, power);
    ghats.at(i) = pow(ghats.at(i), power);
  }
  // orders are bases of the Odometer
  Odometer exp = Odometer(orders);
  // take product of ghats[i]^exp[i]
  long l = 1;
  for (long i=0; i<exp.max(); ++i)
  {
    for (long j=0; j<exp.size(); ++j)
    {
      l *= pow(ghats.at(j), exp.get(j));
    }
    liars.push_back(l);
    exp.spin();
  }
}

/* the vector comps is a list of factored carmichael numbers
Thm: a strong liar iff (a|p) matches for all p dividing n
so this program simply checks that 
Output is liars vector, 1 if a liar for all comps
*/
void naive_tabliars(long bound, const vector< vector<long> > &comps, vector<bool> &liars){
  //initialize the output vector
  liars.reserve(bound+1);
  for(long i=0; i < bound+1; i++){
    liars.push_back(1);
  }

  // for each potential liar or witness a
  for(long a=0; a <= bound; a++){
    cout << a << " : ";  

    // for each composite carmichael number
    for(long i=0; i < comps.size(); i++){
      if( IsCarLiar(a, comps.at(i))) cout << 1 << " ";
      else cout << 0 << " ";    

      if( !IsCarLiar(a, comps.at(i)) ){
        liars.at(i) = 0; // witness for one n means not a liar for all
        break;  
      } //end if a liar for n
    
    } //end for comps
    cout << "\n";
  } // end for on a
}

/* the vector comps can be an list of factored composite numbers here.result in the witnesses vector is a 1 if a is a reliable witness
Very basic - straightforward Miller_Rabin applied for each a, each n
*/
void NaiveReliableWitness(long bound, const vector< vector<long> > &comps, vector<bool> &witnesses){
  //initialize output vector
  witnesses.reserve(bound+1);
  for(long i=0; i < bound+1; i++){
    witnesses.push_back(1);
  }

  vector<long> n;  // factored composite number
  ZZ N;  // multiplied version

  // for each potential witness a
  for(long a=0; a <= bound; a++){
    // for each n in comps
    for(long i=0; i < comps.size(); i++){
      n = comps.at(i);
      // multiply N so we can apply the NTL miller-rabin test
      N = to_ZZ(1);
      for(long j=0; j < n.size(); j++){
      N = N * n.at(j);
      }
      // now if not a witness, set witnesses to 0
      // note MillerWitness requires a < N, so we take a % N
      if(to_ZZ(a) % N != 0){ //if a = 0 mod N, keep it as a witness 
        if( MillerWitness(N, (to_ZZ(a) % N)) != 1) witnesses.at(a) = 0;
      }
    } // end for n in comps
  }//end for a
}


/* a subprogram that returns 1 if a is a liar for n
requires n to be a factored carmichael number, uses theorem stated above.
also requires all factors to be 3 mod 4
*/
bool IsCarLiar(long a, const vector<long> &n){
  // multiply n and check that all factors are 3 mod 4
  long nmult = 1;
  for(long i=0; i < n.size(); i++){
    nmult = nmult * n.at(i);
    if(n.at(i) % 4 != 3) cout << "Error in IsCarLiar: " << n.at(i) << " is not congruent to 3 mod 4\n";
  }
  // now check korselt condition
  for(long i=0; i < n.size(); i++){
    if( (nmult-1) % (n.at(i) - 1) != 0) cout << "Error in IsCarLiar: failed korselt condition with n = " << nmult << " and p = " << n.at(i) << "\n";
  }

  bool output = true; // assume it is a liar
  long first_jacobi = slow_jacobi(a, n.at(0));
  if(first_jacobi == 0) return false; // not relatively prime to p1 means witness 
  
  // now check that the jacobi symbol of the rest of the factors matches
  for(long i=1; i < n.size(); i++){
    if(slow_jacobi(a, n.at(i)) != first_jacobi){
      output = false;  // not all equal means witness
      break;  // no need to continue checking
    }
  }
return output;
}

/* a sieving style search for a reliable witness.  Currently the composites 
must be factored and must be Carmichael numbers 
*/
void SieveReliableWitness(long bound, const vector< vector<long> > &comps, vector<bool> &witnesses, const vector<long> &factors){
 //initialize output vector, assume initially everything a witness
  witnesses.reserve(bound+1);
  for(long i=0; i < bound+1; i++){
    witnesses.push_back(1);
  }

  vector<long> n;  // factored composite number
  long composite;  // incrementor for 
  bool iswitness; 

  // unfortunately we need to generate all the witnesses at once
  vector< vector<bool> > AllWitnesses;
  
  // build the witnesses up one composite at a time
  for(long numcomps = 0; numcomps < comps.size(); numcomps++){
    n = comps.at(numcomps);
    vector<bool> templiars;
    IsLiarOrd2(bound, n, templiars, factors);

    AllWitnesses.push_back(templiars);
  }
  // now check if all are witnesses
  for(long a = 0; a < bound+1; a++){
    iswitness = 1; // assume initially it is a witness
    composite = 0; // interator through comps vector

    //cout << a << ": "; // testing
    while(composite < comps.size() && iswitness == 1){
      if(AllWitnesses.at(composite).at(a) == 1) iswitness = 0;
    
      //cout << AllWitnesses.at(composite).at(a) << " ";
      
      composite++;
    }
    //cout << "\n";
    // if different from default, update witnesses vector
    if(iswitness == 0) witnesses.at(a) = 0; 
  }
}


/* this subprogram returns 1 if a is a liar for n, but now n can be any odd
composite.  Thm from Alford, Granville, Pomerance:  a is a strong liar for n
iff a^(n-1) = 1 mod n and there exists k so that 2^k || l_a(p) for all p | n.
Important that n is given as a sequence of prime factors - it will not be checked
We'll also assume n is carmichael, and do it for all a up to some bound.
*/
void IsLiarOrd2(long bound, const vector<long> &n, vector<bool> &liars, const vector<long> &factors){
  // the main data structure: contains a^d mod p for all p | n
  vector< vector<long> > AllAs;
  liars.reserve(bound+1);
  for(long i=0; i < bound+1; i++){
    liars.push_back(1);  //initially set all a to be liars
  }

  long p;  // for a factor of n
  long d,e;  // for decomposing p-1

  // construct the AllAs vector using PowerAll
  for(long i=0; i < n.size(); i++){
    p = n.at(i);
    // decompose p-1 as 2^e * d where d is odd
    d = largestOddDivisor(p-1);
    e = Ord2(p-1);
   
    // create powers a^d mod p for all a up to bound, then push onto AllAs
    vector<long> A;
    PowerAll(bound, A, d, p, factors);
    AllAs.push_back(A);

  }//end for on prime factors of n
  
  bool isliar;
  long ord2, initialord2;
  long value;

  // now start squaring to find the power of 2 that divides ord_a(p)
  // for a given a, if they are equal across all p then a is a liar
  for(long a = 0; a <= bound; a++){

    // if a is a multiple of p then a is definitely a witness
    // also, a = 0 is a witness by fiat
    if(AllAs.at(0).at(a) == 0 || a == 0){
      liars.at(a)=0;
      continue;
    }

    isliar = 1;  //assume initially it is a liar
    // compute ord2 for the first prime
    p = n.at(0);
    value = AllAs.at(0).at(a);
    initialord2 = 0;
    // we know at this point a is a unit mod p, so while loop will terminate
    while(value != 1){
      value = MulMod(value, value, p);
      initialord2++;
    }

    // now compute ord2 for other primes and compare
    // efficiency issue:  it would be nice if I could quit this loop early if witness
    long i = 0;
    while(i < n.size() && isliar == 1){ 
      // check again if a is a multiple of p
      if(AllAs.at(i).at(a) == 0){
        isliar = 0;
      }else{
        p = n.at(i);
        value = AllAs.at(i).at(a);

        ord2 = 0;
        while(value != 1){
          value = MulMod(value, value, p);
          ord2++;
        }
        // compare ord2 to the first one
        if(ord2 != initialord2){
          isliar = 0;
        }
      }
    i++;
    } //end for compute ord2
    // after checking all p, we know ord2's are equal so a is liar
    liars.at(a) = isliar;
  } //end for a up to bound 
}

/* subroutine.  Given a vector of longs and prime p, changes the vector so that 
entry i contains i^d mod p */
void PowerAll(long bound, vector<long> &A, long d, long p, const vector<long> &factors){
  // resize the vector A, set all entries to 1
  A.reserve(bound+1);
  for(long i=0; i < bound+1; i++){
    A.push_back(1);
  } 

  // now use a sieve technique.  One wrinkle is dealing with prime powers
  long nextprime = 2;
  long primepower = nextprime;
  long powered;  // to store nextprime^d mod p
  long sequence; // for the multiples of primepower
  while(nextprime <= bound){
    // set nextprime to be its dth power mod p
    powered = PowerMod(nextprime, d, p);  
    
    // we need to multiply for all prime powers of nextprime
    while(primepower <= bound){
      sequence = primepower;

      // now we multiply by powered for multiples of the prime power
      while(sequence <= bound){
        A.at(sequence) = MulMod(A.at(sequence),powered,p);
        sequence = sequence + primepower;
      } // while sequence

      // increment primepower
      primepower = primepower * nextprime;
    } // while primepower

    // now increment nextprime and reset primepower
    nextprime++;
    while(nextprime <= bound && factors.at(nextprime) != nextprime) nextprime++;
    primepower = nextprime;
  } // end while
}

/* print the entries of a vector<bool> that are 1 */
void PrintOnes(const vector<bool> &input){
  for(long i=0; i < input.size(); i++){
    if(input.at(i)) cout << i << " ";
  }
  cout << "\n";
}

