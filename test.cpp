#include <ctime>
#include <time.h>
#include <vector>
#include "formulas.h"
#include "tab_carmichael.h"
#include "tab_liars.h"
#include "first_liar.h"
#include <NTL/ZZ.h>
#include <list>
#include <NTL/RR.h>  
#include "sievepractice.h"
#include "lowestprimesieve.h"
#include "tab_psp.h"
#include "DoubleLinkedListArray.h"
NTL_CLIENT


int main() {
  
  long p;
  cout << "Enter a prime power: ";
  cin >> p;
  clock_t duration; // used for timing
  duration = clock();
  long g = firstGenerator(p);
  duration = clock() - duration;
  if (g == p) cout << "Error: input not a prime power." << endl;
  else cout << "The first generator for mult group mod " << p << " is " << g << endl;
  double result = ((double)duration) / CLOCKS_PER_SEC;
  // Output the result of timing
  cout << "It takes " << result << " seconds to find finish all this work.\n";
 /* long n, a;
  int method;
  cout << "Enter a positive integer as the bound:" << endl;
  cin >> n;
  cout << "Enter a positive integer as the base:" << endl;
  cin >> a;
  cout << "Choose a method of tabulation:" << endl;
  cout << " 1) Original   2) Paper   3) Tony's " << endl;
  cin >> method;

  vector<long> f = FactoredSieve(n);

  vector<long> factors; // vector of longs to store factors of n
  vector<long> ints; // vector of indicators of strong pseudoprimes

  clock_t duration; // used for timing
  
  if (method == 1) {
    duration = clock();
    SieveStrongTab(a, n, ints, f);
    duration = clock() - duration;
  }
  else if (method == 2) {
    duration = clock();
    SieveStrongTabOnPaper(a, n, ints, f);
    duration = clock() - duration;
  }
  else if (method == 3) {
    duration = clock();
    SieveStrongTabByTony(a, n, ints, f);
    duration = clock() - duration;
  }
  else {
    cout << "Please choose either 1 or 2." << endl;
    return 0;
  }

  cout << "Tabulating all pseudoprimes...." << endl;

  for (long i=0; i<=n; i++) {
    if (ints.at(i) == 1) {
      cout << i << " is a stong pseudoprime to base " << a << endl;
    }
  }

  double result = ((double)duration) / CLOCKS_PER_SEC;
  // Output the result of timing
  cout << "It takes " << result << " seconds with method " << method << ".\n"; 
*/
/* vector<ZZ> output;
  output = TrivialStrongTab(to_ZZ(2), to_ZZ(100000));

  cout << "Looking at output of TrivialStrongTab\n";
  for(long i = 0; i < output.size(); i++){
    cout << output.at(i) << " ";
  }
  cout << "\n";
 
  long BOUND = 10000;
  long BASE = 2;
  vector<long> sieve;
  sieve = FactoredSieve(BOUND);
  vector<long> pseudo = LinearSieveFermatTab(BASE, BOUND, sieve);
  for(long i=0; i < pseudo.size(); i++){
    cout << pseudo.at(i) << " ";
  }
  cout << "\n";
*/
/*
  mark(sieve);
  primes(sieve);
*/ 

/*
for(long n = 3; n < 2050; n++){
  if(n % 2 == 1 && !ProbPrime(to_ZZ(n))){
    cout << n << " : " << PowerMod(to_ZZ(2), n-1, to_ZZ(n)) << "\n";
  }
}
*/
}

  
