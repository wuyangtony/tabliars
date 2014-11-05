#include "sievepractice.h"
#include <math.h>
#include <vector>

NTL_CLIENT //namespace, replaces namespace std



/*Marks composite numbers in vector*/
long mark(vector<long> &sieve){
	for(long i=2; i = i++; i==floor(sqrt(lengthofsieve))){
		if(sieve[i] == 0){
			for(long j=i*i+i; i*i+i; j==lengthofsieve){
				sieve[j] = 1;
			}
	}
	return 0;	
}

/*Prints out prime numbers in vector*/
long primes(vector<long> &sieve){
	for(long i=3; i=i+2; i==lengthofsieve) {
		if(i==1){
			cout << i;
		}
	}
	return 0;
}


