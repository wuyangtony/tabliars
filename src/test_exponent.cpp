#include <iostream>
#include <vector>
#include "exponent_list.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>
using namespace std;


NTL_CLIENT

int main(int argc, char* argv[]) {
	static const long arr[] = {1,2,3,4};
	vector<long> exponents (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	vector<vector<long> > exps_list = ExponentList(exponents);
	for (int i = 0; i < exps_list.size(); i++) {
	    for (int j = 0; j < exps_list[i].size(); j++) {
	        cout << exps_list[i][j];
	    }
	    cout << endl;
	}
	return 1; 
}