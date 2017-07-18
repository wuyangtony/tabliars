#include "../include/reliable_witness_lchen.h"
#include <vector>


/** This function is a modified version of Andrew's NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<bool> &witnesses, vector<bool> &ifreliable) {
    long IfWitness;

	// cout << "test naive reliable witness comps.size() : " << comps.size() << endl;

    // if reliable is a vector that indicate whether or not this comps have reliable witness. 
    // 
	ifreliable.push_back(0);

	// initialize output vector
	// update: we don't need to use a vector to save the witness

	// check_wit is an object to check if a base is a reliable witness. 
	// for each base (in each for loop), set to 1, 
    // if it is not a witness for a comp, then it as not a reliable witness
	// then change it to 0.
    long check_wit;

	// witnesses.reserve(bound);

 //    long IfWitness = 0;  // 1 means a is a witness for a given composite n
	// for (long i = 0; i < bound; i++) {
	// 	//cout << "allocate vector" << endl; 
	// 	witnesses.push_back(1);
	// }

	// when a = 0, the program cannot enter the inner for loop. 
	for (long a = 1; a < bound; a++) {
        check_wit = 1;
		//cout << "comps.size()" << comps.size() << endl;
		for (long k = 0; k < comps.size(); k++) { 
			// apply miller-rabin test
			// if a % i = 0, then a is neither a strong witness nor a strong liar
			if (to_ZZ(a) % to_ZZ(comps.at(k)) == 0) {
				// witnesses.at(a) = 0;
                check_wit = 0;
				break;
			}
			else {
				// Note that MillerWitness only supports odd composits 
				IfWitness = MillerWitness(to_ZZ(comps.at(k)), (to_ZZ(a) % to_ZZ(comps.at(k))));
				if (IfWitness != 1) {
					// witnesses.at(a) = 0;
                    check_wit = 0;
					break;
				}
			}
			// if a is a reliable witness, check_wit = 1
		}

		if (check_wit == 1) {
			cout << a << " is a reliable witness for the set of composite. Increase the bound.." << endl;
			ifreliable.at(0) = 1;
			//count_witness++;
			return;
		}
	}
	//cout << endl;
    cout << "?????????????" << endl;
	return; 
}

void TestFunction() {
	cout << "test function works" << endl;
}