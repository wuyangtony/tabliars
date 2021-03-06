#include <ctime>
#include <vector>
#include <NTL/ZZ.h> 
#include <NTL/RR.h>
#include "../include/formulas.h"
#include "../include/tab_carmichael.h"
#include "../include/tab_liars.h"
#include "../include/first_liar.h" 
#include "../include/sievepractice.h"
#include "../include/lowestprimesieve.h"
#include "../include/tab_psp.h"
#include "../include/DoubleLinkedListArray.h"
NTL_CLIENT


int main() {

  long n;
  cin >> n;
  vector<long> sieve;
  factoredSieve(n, sieve);
  vector<long> factors;
  getPrimeFactors(n, sieve, factors);
  for (long i=0; i<factors.size(); ++i)
  {
    cout << factors.at(i) << " is a prime factor of " << n << endl;
  }
  /*vector<ZZ> output;
  output = TrivialStrongTab(to_ZZ(2), to_ZZ(100000));

  cout << "Looking at output of TrivialStrongTab\n";
  for(long i = 0; i < output.size(); i++){
    cout << output.at(i) << " ";
  }
  cout << "\n";

  // Ask for user input and creates vector of that length
 long BOUND = 10000;
  long BASE = 2;
  vector<long> sieve;
  sieve = FactoredSieve(BOUND);


  vector<long> pseudo = LinearSieveFermatTab(BASE, BOUND, sieve);
  for(long i=0; i < pseudo.size(); i++){
    cout << pseudo.at(i) << " ";
  }
  cout << "\n";


  mark(sieve);
  primes(sieve);



for(long n = 3; n < 2050; n++){
  if(n % 2 == 1 && !ProbPrime(to_ZZ(n))){
    cout << n << " : " << PowerMod(to_ZZ(2), n-1, to_ZZ(n)) << "\n";
  }
}


  vector<long> sieve = FactoredSieve(bound);

  vector< vector<long> > comps = three_carmichael(bound, sieve);
  print_carslist(comps);

  vector<bool> witnesses1, witnesses2;
  SieveReliableWitness(bound, comps, witnesses1, sieve);
  NaiveReliableWitness(bound, comps, witnesses2);

  for(long i=0; i < witnesses1.size(); i++){
    if(witnesses1.at(i) != witnesses2.at(i)){
       cout << "disagreement at i = " << i << "\n";
       cout << "sieve gives " << witnesses1.at(i) << " naive gives " << witnesses2.at(i) << "\n";
    } 
  }
  cout << "end of check\n";


// does 69 and 95 really only have 2 strong liars
cout << "strong liars for 95:\n";
for(ZZ i = to_ZZ(1); i < 95; i++){
  if(!MillerWitness(to_ZZ(95), i)) cout << i  << " is a liar\n";
}

// more testing - using another method to count composites with two strong liars
  for(long i=1; i <= bound; i++){
    if(trialStrongLiarCount(i) == 2)4
      if(sieve.at(i) == i) cout << i << " is prime and counted\n";
      if(i % 2 == 0) cout << i << " is even and counted\n";
      ncount++;
    }
  cout << "The number of integers up to " << bound << " with two strong liars is " << ncount << "\n";
  cout << "\n";



cout << "counting n with two strong liars up to " << bound << " which is 10 to the power " << power << "\n";

time(&start);

// strong liar count with sieve method
ncount = sieveTwoStrongLiarsCount(bound);

time(&end);

cout << ncount << " : number with 2 strong liars up to 10 to the " << power << "\n";RR ratio = to_RR(ncount-1 + 0.0);
ratio = ratio * log(log(log(bound)));
cout << "(count-1) * logloglog x is " << ratio << "\n";
cout << "time taken is " << difftime(end,start) << "\n";

 // testing strong liar count
for(long n = 1; n < bound; n++){
    ncount = StrongLiarCount(n);
    //cout << n << " has " << ncount << " number of strong liars\n";
    if(ncount == 2 || ncount == 1) numone++;
}
  cout << numone << " : number with 2 or 1 Strong liars up to " << bound << " \n";
  RR ratio = to_RR(numone + 0.0);
  ratio = ratio * log(log(log(bound)));  
  cout << ratio << "\n";


  // test the Factor command
  list<long> factors;
  for(long n = 0; n < 100; n++){
    Factor(n, factors);
    list<long>::iterator i;
    for( i=factors.begin(); i != factors.end(); i++){
      cout << *i << " ";
    }
    cout << "\n";
    factors.clear();
  }	*/

  return 0;
}