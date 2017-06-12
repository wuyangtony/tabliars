#include <iostream>
#include "reliable_witness_lchen.h"
#include "formulas.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>

NTL_CLIENT

int main(int argc, char* argv[]) {
	long bound_a = 5000000; // bound of witnesses
	long bound_n = 2047; // bound of composits numbers
	vector<long> sieve;
	vector<long> c; // vector of composite up to bound
	vector<bool> a; // all possible base up to bound 
	
	cout << "0 < a <= " << bound_a << endl;
	cout << "0 < n <= " << bound_n << endl;	

	factoredSieve(bound_n, sieve);

	// generate an odd composits vector
	for (long comp = 9; comp < sieve.size(); comp++) {
		if (sieve.at(comp) != comp && comp % 2 != 0) {
			c.push_back(comp);
		}
	}
	cout << "A set of odd composit numbers: ";

	// generate a witnesses vector
	//cout << "Reliable witnesses: ";
 	for (long i=0; i < c.size(); i++) {
 		cout << c.at(i) << " ";
 	}
	cout << " " << endl;

	// generate reliable witnesses using function in reliable_witness_lchen.cpp
 	NewNaiveReliableWitness(bound_a, c, a);
// 	for (long i = 0; i < a.size(); i++) {
// 		if (a.at(i) == 1) {
// 			cout << i << " ";
//		}
// 	}
 	cout << endl;
 	return 0;
}
