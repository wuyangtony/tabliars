#include "sievepractice.h"
#include <math.h>
#include <vector>

NTL_CLIENT //namespace, replaces namespace std



/*Marks composite numbers in vector*/
long mark(vector<long> &sieve){
	long lengthofsieve = sieve.size();
	for(long i=2; i<lengthofsieve; i++){
		if(sieve[i] == 0){
			for(long j=2*i; j<lengthofsieve; j+=i){
				sieve[j] = 1;
			}
 		}
	}
	return 0;	
}

/*Prints out prime numbers in vector*/
long primes(vector<long> &sieve){
	long lengthofsieve = sieve.size();
	for(long i=3; i<lengthofsieve; i+=2){
		if(sieve[i]==0){
			cout << i << "\n";
		}
	}
	return 0;
}


