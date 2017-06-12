#include "../include/tab_carmichael.h"

NTL_CLIENT

/* Finds all Carmichaels with three prime factors smaller than bound
Uses method of Pinch from MathComp 1993, 61, tabulating cars up to 10^15
Sieve is the result of calling FactoredSieve from formulas.h
*/
//vector< vector<long> > three_carmichael(long bound){
vector< vector<long> > three_carmichael(long bound, const vector<long> &sieve){  
  // list of the factorizations of carmichael numbers found
  vector< vector<long> > cars = vector< vector<long> >();

  long p1bound = pow(bound, 1.0/3); // smallest prime at most cube root
  long p2, p3;  // for the other two primes
  long delta;  // I think its a discriminant, defined as CD - p1^2
  long N;  // for the hoped for carmichael
  long lowCbound; // for defining C

  // this is the main loop
  for(long p1 = 2; p1 < p1bound; p1++){
    if(sieve.at(p1) == p1){  //then p1 is prime
      // C and D come from Pinch's Prop 2
      for(long D = 2; D < p1; D++){
        // p1^2 < CD < P^2 * (p1+3)/(p1+1)
	lowCbound = (p1*p1)/D + 1;        
        for(long C = lowCbound; C < (p1*p1*(p1+3))/(D*(p1+1)) + 1; C++){
 	  delta = C*D - p1*p1;
          // p2 and p3 need to be integers
          // we define p2 = (p1-1)*(p1+D)/delta + 1, p3 = (p3-1)*(p3+D)/delta + 1
          p2 = (p1-1)*(p1 + D);
          p3 = (p1-1)*(p1 + C);
          if(p2 % delta == 0 && p3 % delta == 0){
            p2 = p2/delta + 1;
            p3 = p3/delta + 1;
            if(sieve.at(p2)==p2 && sieve.at(p3)==p3){ // if both primes
              //if n<bound and satisfies korselt then add to the list of carmichaels
	      N = p1*p2*p3;            
              if( N < bound && (N-1)%(p1-1) == 0 && (N-1)%(p2-1) == 0 && (N-1)%(p3-1) == 0 && p1 != p2 && p2 != p3){
		vector<long> num = vector<long>();
                num.push_back(p1); num.push_back(p2); num.push_back(p3);
  		cars.push_back(num);
              } // end if carmichael
            }//end if both prime
	  }//endif integers
        } //endfor C
      } // endfor D
    } // endif is p1 prime
  } //endfor p1
return cars;
} // end function


/* simply prints a structure of the form vector< vector<long> >
*/
void print_carslist(const vector< vector<long> > &cars){
  long n; // will be the multiplied number.
  for(long i=0; i < cars.size(); i++){
    n = 1;  // reset n
    for(long j=0; j < cars.at(i).size(); j++){
      cout << cars.at(i).at(j) << " ";
      n = n * cars.at(i).at(j);
    }
    cout << " : mod 4 : ";
    for(long j=0; j < cars.at(i).size(); j++){
      cout  << cars.at(i).at(j) % 4 << " ";
    }
    cout << " : " << n;
    cout << "\n";
  }
}

/* returns the subset of a carmichael list where all the factors are 
congruent to 3 mod 4
*/
vector< vector<long> > subset3mod4(const vector< vector<long> > &cars){
  vector< vector<long> > subset;
  vector<long> n;  // to store a particular carmichael number temporarily
  bool keep;

  // for all carmichael numbers in the cars list
  for(long i = 0; i < cars.size(); i++){
    n = cars.at(i);
    keep = 1;
    for(long j=0; j < n.size(); j++){
      // don't keep n if even one factor is not 3 mod 4
      if(n.at(j) % 4 != 3) keep = 0;
    }
    if(keep) subset.push_back(n);
  }
return subset;
}


