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
long BOUNDPOW = 9;

long bound = power_long(10, BOUNDPOW);
time_t start1, end1, start2, end2, start3, end3, start4, end4; // for timings

// FactoredSieve returns array where nth entry contains smallest prime factor of n
time(&start1);
vector<long> sieve;
sieve.reserve(bound+1);
factoredSieve(bound, sieve);
time(&end1);
cout << "time taken creating factor sieve is " << difftime(end1, start1) << "\n";

long ncount=0;  // stores the count of odd composites with two strong liars

/*
time(&start2);
// count the number of odd composites with two strong liars using definition
for(long i = 3; i <= bound; i = i+2){
  if(sieve.at(i) != i && StrongLiarCount(to_ZZ(i)) == to_ZZ(2)) ncount++;
}
time(&end2);

cout << "bound is " << bound << " and ncount is " << ncount;
cout << " time taken is " << difftime(end2, start2) << "\n";

time(&start3);
// count the number of composites with two strong liars using Monier
ncount = 0;
for(long i = 3; i <= bound; i=i+2){
  if(sieve.at(i) != i && trialStrongLiarCount(i) == 2) ncount++;
}
time(&end3);

cout << "bound is " << bound << " and ncount is " << ncount ;
cout << " time taken is " << difftime(end3, start3) << "\n";
*/

time(&start4);
// finally, count the number of composites with two strong liars using Shallue sieve
ncount = sieveTwoStrongLiarsCount(bound);
time(&end4);

cout << "bound is 10 to the " << BOUNDPOW << " and ncount is " << ncount;
cout << " time taken is " << difftime(end4, start4) << "\n";

RR ratio = to_RR(to_RR(ncount)/to_RR(bound));
ratio = ratio * log(log(log(bound)));
cout << "(count)/x * logloglog x is " << ratio << "\n";




return 0;
} 

