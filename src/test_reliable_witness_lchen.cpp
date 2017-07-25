#include <iostream>
#include <vector>
#include "../include/reliable_witness_lchen.h"
#include "../include/formulas.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>

NTL_CLIENT

int main(int argc, char* argv[]) {
	// long IfWitness;
	// IfWitness = MillerWitness(to_ZZ(2047), (to_ZZ(2) % to_ZZ(2047)));
	// cout << IfWitness << end;
	long bound_a = 2046; // bound of witnesses
	long bound_n = 2046; // bound of composits numbers
	long count_wit;
	vector<long> sieve;
	vector<long> c; // vector of composite up to bound
	vector<bool> a; // all possible base up to bound 
	vector<bool> ifwit;
	
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
 	NewNaiveReliableWitness(bound_a, c, a, ifwit, count_wit);
// 	for (long i = 0; i < a.size(); i++) {
// 		if (a.at(i) == 1) {
// 			cout << i << " ";
//		}
// 	}
 	cout << endl;
 	return 0;
}
