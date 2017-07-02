#include <iostream>
#include <vector>
#include <math.h> 
using namespace std;

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

	comps_list.reserve(exps_list.size());

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