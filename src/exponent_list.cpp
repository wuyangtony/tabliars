#include <iostream>
#include <vector>
using namespace std;

// Input: vector<long>, stores exponents (k1, k2, ..., kn)
// Output: vector<vector<long>>, each element <j1, j2, ..., jn>, 0 < ji < ki
vector<vector<long> > ExponentList(const vector<long> &exponents) {

	// the height of the metrix will be k1+1 * k2+1 * k3+1 * ... * kn + 1
	// the weight the vector metrix which is exponents.size
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