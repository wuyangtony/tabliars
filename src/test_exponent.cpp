#include "../include/Odometer.h"
#include "../include/exponent_list.h"
#include "../include/reliable_witness_lchen.h"
#include "../include/tab_psp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <NTL/ZZ.h>
#include <NTL/RR.h>

using namespace std;

NTL_CLIENT


int main() {
	ofstream myfile;
	ofstream wit_file;
	myfile.open("rel_wit5.csv");
	wit_file.open("tab_wit5.csv");

	vector<long> expo_gen;
	// vector<long> comps_list;
	vector<long> comps_set;
	// long arr[] = {1,2,3}; // exponent list 
	long exponent = 1;
	long arr2[] = {3, 5, 7, 11, 13}; // bases
	int ifwit;
	int arr2_size = sizeof(arr2)/sizeof(arr2[0]);
	vector<long> witness;
	vector<bool> ifreliable;
	vector<int> prev_height;
	prev_height.push_back(0);
	long new_bound;
	long count_wit;
	long prev_bound;


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

		NewNaiveReliableWitness(bound, comps_set, witness, ifreliable, count_wit);
		wit_file << bound << "," << count_wit << "," << "0" << "," << "0" << ",";
		for (int i = 0; i < witness.size(); i++) {
			wit_file << witness.at(i) << ",";
		}
		wit_file << endl;
		wit_file.close();


		if (ifreliable.at(0) == 0) {
			cout << "this set doesn't have reliable witness." << endl;
			cout << "the exponents are " << exponent << endl;
			break;
		}
		else {
			//cout << "Increase the bound of a ..." << endl; 
			// Instead of increase the bound of a, we can add a base-a spsp to comps_set,
			// then test the percentage of reliable witness again.
			// The first a-based spsp can be generated by modified version of TrivialStrongTab
			// in tab_psp.cpp. 
			vector<long> base_set; // add a base-a spsp to comp_set
			for (int i = 2; i < 100000; i++) {
				for (int j = 0; j < 10; j++) {
					if (i == j * j) {
						i++;
						break;
					}
				}
				base_set.push_back(i);
			}

			// cout << "the base_set is " ;
			// for (int i = 0; i < base_set.size(); i++) {
			// 	cout << base_set.at(i) << " ";
			// }
			cout << endl;
			long spsp_bound = 100000000;
			for (int i = 0; i < base_set.size(); i++) {
				long first_i_spsp = FirstStrongTab(base_set.at(i), spsp_bound);
				if (first_i_spsp == 0) {
					continue;
				}
				cout << "add a base-" << base_set.at(i) <<" spsp " << first_i_spsp << " to comps_set" << endl;
				// if (i == 0) {
				// 	prev_bound = bound;
				// }
				// else {
				// 	prev_bound = new_bound;
				// }
				// Gen_New_bound(new_bound, comp_bases, first_i_spsp, prev_bound);
				
				// cout << "the new bound is " << new_bound << endl;
				comps_set.push_back(first_i_spsp);
				//NewNaiveReliableWitness(new_bound, comps_set, a, ifreliable, count_wit);
				myfile.open("rel_wit5.csv", std::ios::app);
				wit_file.open("tab_wit5.csv", std::ios::app);
				NewNaiveReliableWitness(bound, comps_set, witness, ifreliable, count_wit);
				if (ifreliable.at(0) == 0) break;
				myfile << bound << "," << count_wit << "," << base_set.at(i) << "," << first_i_spsp << "," << endl;
				wit_file << bound << "," << count_wit <<"," << base_set.at(i) << "," << first_i_spsp << ",";
				for (int i = 0; i < witness.size(); i++) {
					wit_file << witness.at(i) << ",";
				}
				wit_file << endl;
				myfile.close();
				wit_file.close();
			}
		}

		cout << "now increase the bound.." << endl;
		exponent = exponent + 1;
		comps_set.clear();
	}

	// long base_set[] = {2, 3, 5, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, };
	// int base_set_size = sizeof(base_set)/sizeof(base_set[0]);
	// long spsp_bound = 1000000;
	// for (int i = 0; i < base_set_size; i++) {
	//  	long first_i_spsp = FirstStrongTab(base_set[i], spsp_bound);
	//  	cout << "base-" << base_set[i] <<" spsp is " << first_i_spsp << endl;
	// }
	// cout << "now check the ProbPrime function... " << endl;
	// long prime_set[] = {3, 5, 7, 11, 13, 17};
	// for (int i = 0; i < 6; i++) {
	// 	long probprime = ProbPrime(prime_set[i]);
	// 	cout << "for prime " << prime_set[i] << ", the ProbPrime is " << probprime << endl;
	// }
	myfile.close();
	return 1; 
}
