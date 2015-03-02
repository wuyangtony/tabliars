#include <ctime>
#include <time.h>
#include <math.h>
#include <vector>
#include "formulas.h"
#include "tab_carmichael.h"
#include "tab_liars.h"
#include "first_liar.h"
#include <NTL/ZZ.h>
#include <list>
#include <NTL/RR.h>
#include "sievepractice.h"

NTL_CLIENT

/* This file generates an executable.  It is the program related to the Two Strong Liars 
Project with Eric Bach.  The goal is to count the number of odd composites with two 
strong liars up to x.

Note: currently user has to modify the variable BOUNDPOW.  The bound for all programs run 
will then be 10^(BOUNDPOW)
*/

int main(){

// BOUNDPOW is the power of 10 that forms the upper bound of all calculations. 
// bound is the resulting integer value
long BOUNDPOW = 5;

ZZ bound = power_ZZ(10, BOUNDPOW);

// FactoredSieve returns array where nth entry contains smallest prime factor of n
vector<long> sieve = FactoredSieve(1000);

long ncount=0;  // stores the count of odd composites with two strong liars

cout << "bound is " << bound << " and ncount is " << ncount << "\n";

cout << MillerWitness(to_ZZ(4), to_ZZ(3)) << "\n";

for(ZZ i = to_ZZ(3); i < to_ZZ(30); i = i+2){
  cout << i << ": " << StrongLiarCount(i) << "\n";
}

/*
// more testing - using another method to count composites with two strong liars
  for(long i=1; i <= bound; i++){
    if(trialStrongLiarCount(i) == 2){
      if(sieve.at(i) == i) cout << i << " is prime and counted\n";
      if(i % 2 == 0) cout << i << " is even and counted\n";
      ncount++;    }
  }
  cout << "The number of integers up to " << bound << " with two strong liars is " << ncount << "\n";
  cout << "\n";
*/

/*
cout << "counting n with two strong liars up to " << bound << " which is 10 to the p
ower " << power << "\n";
time(&start);

// strong liar count with sieve method
ncount = sieveTwoStrongLiarsCount(bound);

time(&end);

cout << ncount << " : number with 2 strong liars up to 10 to the " << power << "\n";
RR ratio = to_RR(ncount-1 + 0.0);
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
*/



return 0;
} 

