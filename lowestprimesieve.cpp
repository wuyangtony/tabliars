#include "lowestprimesieve.h"
#include <math.h>
#include <vector>

NTL_CLIENT //namespace, replaces namespace std

/*Marks composite numbers in vector*/
long lowestprime(vector<long> &sieve){
	long lengthofsieve = sieve.size();
	for(long i=2; i<lengthofsieve; i++){
		if(sieve[i] == 0){
			for(long j=2*i; j<lengthofsieve; j+=i){
				sieve[j] = i;
			}
		}
	}
	return 0;
}

/*Prints out all numbers indicating lowest prime factor*/
long prime(vector<long> &sieve){
	long lengthofsieve = sieve.size();
	for(long i=3; i<lengthofsieve; i++){ 
			cout << sieve[i] << ":" << i << "\n";
	}
	return 0;
}
