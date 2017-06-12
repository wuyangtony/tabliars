#include <ctime>
#include <time.h>
#include "formulas.h"
#include "tab_carmichael.h"
#include "tab_liars.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>

NTL_CLIENT

int main(int argc, char* argv[]){
 
  time_t start, end; // for timings
 
  // bound is 10^power.  Main driver of the complexity of what follows 
  // if no input argument, default power is 3
  long power = 3; 
  long bound = 1;
 
  // if there is input, set power to that number
  if(argc > 1) power = atoi(argv[1]);

  // note since bound not a ZZ, we're limited to power < 10 on 32-bit machines
  for(long i=0; i < power; i++){
    bound = bound  * 10;  
  }

  // more than one program requires all integers to be factored
  vector<long> sieve;
  factoredSieve(bound, sieve);

  // we'll generate all 3-Carmichaels up to bound and store in comps
  vector< vector< long > > comps = three_carmichael(bound, sieve);

  // run both versions to compare their timings
  long reliablewitnesscount = 0;
  time(&start);

  vector<bool> witnesses;
  NaiveReliableWitness(bound, comps, witnesses);
  time(&end);  

  for(long i=0; i < witnesses.size(); i++){
    if(witnesses.at(i) == 1) reliablewitnesscount++;
  }

  cout << "Naive count of reliable witnesses\n";
  cout << "Found " << reliablewitnesscount << " reliable witnesses up to 10 to the " << power << "\n";
  cout << "time taken is " << difftime(end,start) << "\n";
  
  // now do the same thing for the sieve version
  reliablewitnesscount = 0;
  witnesses.clear(); 
 
  time(&start);

  SieveReliableWitness(bound, comps, witnesses, sieve);
  time(&end);

  for(long i=0; i < witnesses.size(); i++){
    if(witnesses.at(i) == 1) reliablewitnesscount++;
  }
 
  cout << "\n";
  cout << "Sieve count of reliable witnesses\n";
  cout << "Found " << reliablewitnesscount << " reliable witnesses up to 10 to the " << power << "\n";
  cout << "time taken is " << difftime(end,start) << "\n";


return 0;
}


