#include <ctime>
#include <vector>
#include <NTL/ZZ.h> 
#include <NTL/RR.h>
#include "formulas.h"
NTL_CLIENT

// This file is created by Tony Liu specifically testing whether Tony's
// conjecture is true when each prime candidate get significantly large
int main() {
	cout << "Test 2: Last time I've reached the runtime limit before reaching the bound. This time I'll make the runtime longer, which will be 48 hours, all the way until next time we meet. BTW, I forgot to mention last time that the bound actually set the range for prime squared. That means with 2^30 as the bound, the actual range of prime I'm able to test is 2^15, which is about 32000, which is not quite 'large', but at least it can provide with some guidance for the next step." << endl;
	const long x = 1;
	const long bound = x << 30;
	cout << "The bound is " << bound << endl;
	long y; // keep track of the actual prime
	long itself, squared;
	clock_t duration; // used for timing
	cout << "Creating the factored sieve up to the bound...." << endl;
  	duration = clock();
	vector<long> boundsieve = FactoredSieve(bound-1);
	duration = clock() - duration;
	double result = ((double)duration) / CLOCKS_PER_SEC;
	cout << "Factored sieve up to bound created." << endl;
	cout << "It takes " << result << " seconds to create this sieve." << endl;
	duration = clock();
	for (long p=3; p*p<=bound; p++) {
		// For convenience
		if (p % 1000 == 0) {
		    cout << "Reached the milestone of " << p << endl;
		    cout << "Continued." << endl;
		}
		// Loop thru only odd prime numbers
		if (boundsieve.at(p) == p) {
		    itself = firstGenerator(p, boundsieve);
		    squared = firstGenerator(p*p, boundsieve);      
		}
		// Compare itself and squared
		if (itself != squared) {
		    cout << "Congratulations! The first such odd prime number is " << p << ".\n";
		    return 0;
		}
		y = p;
	}
	duration = clock() - duration;
	result = ((double)duration) / CLOCKS_PER_SEC;
	result = result / 60.0;
	cout << "Unfortunately there is no such prime within " << y << ".\n";
	cout << "It takes " << result << " minutes to finish that." << endl;
	return 0;
}
