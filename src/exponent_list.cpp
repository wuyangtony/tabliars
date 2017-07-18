#include <iostream>
#include <vector>
#include <math.h> 
#include <cstdlib>
#include "../include/Odometer.h"
using namespace std;

void OdometerGen(const vector<long> &exponents, const vector<long> &comp_bases, vector<long> &comps_set, vector<int> &prev_height) {
	// exception check 
	if (exponents.size() != comp_bases.size()) {
		cout << "the bases are not valid. " << endl;
		return;
	}
	long temp_comp;
	long height = 1;
	// counting the height of the metrix
	for (int i = 0; i < exponents.size(); i++) {
		height = height * (exponents.at(i) + 1);
	}
	vector<long> odo_bases;
	odo_bases.reserve(exponents.size());
	for (int i = 0; i < exponents.size(); i++) {
		odo_bases.push_back(exponents.at(i) + 1);
	}
	// comps_set.reserve(height);
	// cout << "in OdemeterGen, the height is " << height << endl; 
	Odometer o(odo_bases);
	long curheight;
	for(curheight = 0; curheight < height; curheight++) {
		//cout << "the generated exp_list is " << o << endl;
		o.spin(1);
		// check if the addition of the exponents is larger than 1
		long addition = 0;
		for(long i = 0; i < o.size(); i++) {
			addition += o.get(i);
		}
		if (addition > 1) {
			long comp = 1;
			for (int j = 0; j < o.size(); j++) {
				temp_comp = pow(comp_bases[j], o.get(j));
				comp = comp * temp_comp;
			}
			comps_set.push_back(comp);
		}
	}
	cout << " check curheight is " << curheight << endl; 
	cout << "In the OdometerGen, the comps_set size is " << comps_set.size() << endl; 
	prev_height.at(0) = curheight;
	return;
}

// Need a function to autometic generate two vectors. 
// One is for bases, one is for exponents. 
// Note thet the size of the two vectors should be the same. 
// Two ways to change the bound. one is just increasing the value of exponents;
// another way is adding another prime bases. 
// If we only increase the value of exponents, we will have repeat work to do. 
// In another words, we will check a range of composit number repeatedly. 


// Set the exponents to be the same, then add the base. 
// (need function: generate next prime number)
// void BoundGen1(vector<long> &exponents, vector<long> &comp_bases, base) {

// }

// Set the base to be the same, then increase the exponents. 
void BoundGen2(vector<long> &expo_gen, const vector<long> &comp_bases, long exponent) {
	for (int i = 0; i < comp_bases.size(); i++) {
		expo_gen.at(i) = exponent;
	}
}


// ----------------------- previous functions, not be used currently -----------------------


// Input: vector<long>, stores exponents (k1, k2, ..., kn)
// Output: vector<vector<long>>, each element <j1, j2, ..., jn>, 0 < ji < ki
vector<vector<long> > ExponentList(const vector<long> &exponents) {

	// the height of the metrix will be k1+1 * k2+1 * k3+1 * ... * kn + 1
	// the width the vector metrix is exponents.size
	// cout << "exponent size: " << exponents.size() << endl;

	long height = 1;
	// counting the height of the metrix
	for (int i = 0; i < exponents.size(); i++) {
		height = height * (exponents.at(i) + 1);
	}
	long width = exponents.size();
	vector<vector<long> > exps_list(height, vector<long> (width,1));
	long reptition = 1;
	for (int col = width - 1; col >= 0; col--) {
		long exp = 0;
		long count = 1;
		if (col != width - 1) {
			reptition = reptition * (exponents.at(col + 1) + 1);
		}
		for (int row = 0; row < height; row++) {
			// for the rightmost column
			if (exp == exponents.at(col) + 1) {
				exp = 0;
			}
			exps_list[row][col] = exp;
			if (col == width - 1) {
				exp++;
			}
			else {
				if (count == reptition) {
					count = 1;
					exp++;
				}
				else count++;
			}
		}
	}

	for (int i = 0; i < height; i++) {
		long comp = 0;
		for (int j = 0; j < width; j++) {
			comp = comp + exps_list[i][j];
		}
		//cout << comp << endl;
		if (comp < 2) {
				exps_list.erase(exps_list.begin()+i);
				height--;
				i--;
		}
	}
	return exps_list;
}


// I have a question here: why when I use function type void, data cannot pass by reference. 
// The parameters are just place holders but not passed data here. 
vector<long> CompsGen(vector<vector<long> > &exps_list, const vector<long> &comp_bases) {

	// condition check
	long temp_comp = 0;
	cout << comp_bases.size() << endl;
	if (exps_list[1].size() != comp_bases.size()) {
		cout << "the bases are not valid. " << endl;
		return comp_bases;
	}
	for (int i = 0; i < exps_list.size(); i++) {
		for (int j = 0; j < comp_bases.size(); j++) {
			// for each row, generate the corresponding composite. 
			// the composite k will be bases[j]^exp_list[j]
			//cout << "comp_bases[j] is " << comp_bases[j] << ",exps_list is " << exps_list[i][j] << endl;
			temp_comp = pow(comp_bases[j], exps_list[i][j]);
			//cout << "temp_comp is " << temp_comp << endl;
			if (j == 0) {
				exps_list[i][j] = temp_comp;
			}
			else {
				exps_list[i][j] = exps_list[i][j-1] * temp_comp;
			}
		}
	}
	return comp_bases;
}

void CompsGen2(const vector<vector<long> > &exps_list, const vector<long> &comp_bases, vector<long> &comps_list) {
	// condition check
	long temp_comp;
	cout << comp_bases.size() << endl;
	if (exps_list[1].size() != comp_bases.size()) {
		cout << "the bases are not valid. " << endl;
		return;
	}
	for (int i = 0; i < exps_list.size(); i++) {
		long comp = 1;
		for (int j = 0; j < comp_bases.size(); j++) {
			temp_comp = pow(comp_bases[j], exps_list[i][j]);
			comp = comp * temp_comp;
		}
		comps_list.push_back(comp);
	}
	return;
}