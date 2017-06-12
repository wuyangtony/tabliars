#include <iostream>
#include "formulas.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>

NTL_CLIENT

int main(int argc, char* argv[]) {
	long a = 167780; // bound of witnesses
	long bound_n = 2047; // bound of composits numbers
	long IfWitness = 0;
	vector<long> sieve;
	vector<long> c; // vector of composite up to bound
	factoredSieve(bound_n, sieve);

	// generate an odd composits vector
	for (long comp = 9; comp < sieve.size(); comp++) {
		if (sieve.at(comp) != comp && comp % 2 != 0) {
			//c.push_back(comp);
			IfWitness = MillerWitness(to_ZZ(comp), (to_ZZ(a) % to_ZZ(comp)));
			if (IfWitness != 1) {
				cout << a << " is not a reliable witness."<< endl;
				return -1;
			}
		}
	}
	
	cout << a << " is a reliable witness" << endl;
	return 0;
}
