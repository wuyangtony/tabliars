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
long BOUNDPOW = 4;

long bound = power_long(10, BOUNDPOW);
time_t start, end; // for timings

// FactoredSieve returns array where nth entry contains smallest prime factor of n
time(&start);
vector<long> sieve = FactoredSieve(bound);
time(&end);
cout << "time taken creating factor sieve is " << difftime(end, start) << "\n";

long ncount=0;  // stores the count of odd composites with two strong liars

time(&start);
// count the number of odd composites with two strong liars using definition
for(long i = 3; i <= bound; i = i+2){
  if(sieve.at(i) != i && StrongLiarCount(to_ZZ(i)) == to_ZZ(2)) ncount++;
}
time(&end);

cout << "bound is " << bound << " and ncount is " << ncount;
cout << " time taken is " << difftime(end, start) << "\n";

time(&start);
// count the number of composites with two strong liars using Monier
ncount = 0;
for(long i = 3; i <= bound; i=i+2){
  if(sieve.at(i) != i && trialStrongLiarCount(i) == 2) ncount++;
}
time(&end);

cout << "bound is " << bound << " and ncount is " << ncount ;
cout << " time taken is " << difftime(end, start) << "\n";

time(&start);
// finally, count the number of composites with two strong liars using Shallue sieve
ncount = sieveTwoStrongLiarsCount(bound);
time(&end);

cout << "bound is " << bound << " and ncount is " << ncount;
cout << " time taken is " << difftime(end, start) << "\n";

/*
for(long i = 3; i < 100; i = i+2){
  cout << i << ": " << StrongLiarCount(to_ZZ(i)) << " " << trialStrongLiarCount(i) << "\n";
}
*/


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

