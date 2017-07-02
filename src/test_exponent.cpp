#include <iostream>
#include <vector>
#include "../include/exponent_list.h"
#include "../include/reliable_witness_lchen.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>
using namespace std;


NTL_CLIENT

int main(int argc, char* argv[]) {
	vector<long> comps_list;
	long arr[] = {1,2,3}; // exponent list 
	long arr2[] = {3,5,7}; // bases
	int arr_size = sizeof(arr)/sizeof(arr[0]);
	vector<bool> a;

	long bound = 1;
	//long temp;
	for (int i = 0; i < arr_size; i++) {
		//temp = pow(arr2[i], arr[i]);
		bound = bound * pow(arr2[i], arr[i]);
		//cout << "for loop bound " << bound << endl;
	}

	vector<long> exponents (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	vector<long> comp_bases (arr2, arr2 + sizeof(arr) / sizeof(arr2[0]) );


	// cout << comp_bases.size();
	vector<vector<long> > exps_list = ExponentList(exponents);
	for (int i = 0; i < exps_list.size(); i++) {
	    for (int j = 0; j < exps_list[i].size(); j++) {
	        cout << exps_list[i][j];
	    }
	    cout << endl;
	}

	// Error: segmentation fault: 11
	//CompsGen(exps_list, comp_bases);
	CompsGen2(exps_list, comp_bases,comps_list);


	cout << "after generate composites." << endl;
	// for (int i = 0; i < exps_list.size(); i++) {
	//     for (int j = 0; j < exps_list[i].size(); j++) {
	//         cout << exps_list[i][j];
	//     }
	//     cout << endl;
	// }

	// for (int i = 0; i < exps_list.size(); i++) {
	//     cout << exps_list[i][exps_list[i].size() - 1];
	//     cout << endl;
	// }

	for (int i = 0; i < comps_list.size(); i++) {
		cout << comps_list[i] << endl;
	}

	NewNaiveReliableWitness(bound, comps_list, a);


	//TestFunction();
	//cout << bound << endl;

	//cout << "11111111111" << endl;

	exps_list.clear();
	
	return 1; 
}