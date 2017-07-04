#include "../include/Odometer.h"
#include "../include/exponent_list.h"
#include "../include/reliable_witness_lchen.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <NTL/ZZ.h>
#include <NTL/RR.h>
using namespace std;


NTL_CLIENT

int main() {
	vector<long> expo_gen;
	// vector<long> comps_list;
	vector<long> comps_set;
	// long arr[] = {1,2,3}; // exponent list 
	long exponent = 2;
	long arr2[] = {3, 5, 7, 11, 13}; // bases
	int ifwit;
	int arr2_size = sizeof(arr2)/sizeof(arr2[0]);
	vector<bool> a;
	vector<bool> ifreliable;
	vector<int> prev_height;
	prev_height.push_back(0);

	// vector<long> exponents (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	vector<long> comp_bases (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	for (int i = 0; i < comp_bases.size(); i++) {
		expo_gen.push_back(exponent);
	}

	for (int i = 0; i < 10; i++) {
		long bound = 1;

		for (int j = 0; j < arr2_size; j++) {
			bound = bound * pow(arr2[j], exponent);
		}

		cout << "the bound is: " << bound << endl;

		BoundGen2(expo_gen, comp_bases, exponent);
		cout << "now the exponents are: ";
		for (int k = 0; k < expo_gen.size(); k++) {
			cout << expo_gen.at(k) << " ";
		}
		cout << endl;

		OdometerGen(expo_gen, comp_bases, comps_set, prev_height);

		cout << "after calling OdometerGem, the size of the comps_set is " << comps_set.size() << endl;
		cout << "test reliable witness... " << endl;

		NewNaiveReliableWitness(bound, comps_set, a, ifreliable);

		if (ifreliable.at(0) == 0) {
			cout << "this set doesn't have reliable witness." << endl;
			cout << "the exponents are " << exponent << endl;
			break;
		}

		exponent = exponent + 1;
	}
	//vector<vector<long> > exps_list = ExponentList(exponents);
	// for (int i = 0; i < exps_list.size(); i++) {
	//     for (int j = 0; j < exps_list[i].size(); j++) {
	//         cout << exps_list[i][j];
	//     }
	//     cout << endl;
	// }

	//CompsGen(exps_list, comp_bases);
	// CompsGen2(exps_list, comp_bases,comps_list);

	// cout << "after generate composites." << endl;

	// for (int i = 0; i < comps_list.size(); i++) {
	// 	cout << comps_list[i] << endl;
	// }

	//cout << "start to test odometer..." << endl;
	
	// OdometerGen(exponents, comp_bases, comps_set);
	// for (int i = 0; i < comps_set.size(); i++) {
	// 	cout << comps_set[i] << endl;
	// }

	// NewNaiveReliableWitness(bound, comps_list, a);


	//exps_list.clear();
	
	return 1; 
}