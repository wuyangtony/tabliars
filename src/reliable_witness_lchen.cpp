#include "reliable_witness_lchen.h"
#include <vector>


/** This function is a modified version of Andrew's NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<bool> &witnesses) {
	// initialize output vector
	
	// for (int i = 0; i < comps.size(); i++) {
	// 	cout << comps[i] << " ";
	// }
	// cout << endl;

	witnesses.reserve(bound);
        long IfWitness = 0;  // 1 means a is a witness for a given composite n
	for (long i=0; i < bound; i++) {
		witnesses.push_back(1);
	}
	cout << "reliable witnesses are: ";
	long count = 0;
	cout << " test bound = " << bound << endl;
	cout << " number of comps = " << comps.size() << endl;
	for (long a=0; a < bound; a++) {
		for (long i = 0; i < comps.size(); i++) {
			// cout << "for loop count " << count << endl;
			// cout << " bound = " << a << endl;
			// cout << " comps = " << comps[i] << endl;
			count++;
			// apply miller-rabin test
			// if a % i = 0, then a is neither a strong witness nor a strong liar
			// cout << to_ZZ(a) << endl;
			// cout << to_ZZ(comps.at(i)) << endl;
			// cout << to_ZZ(a) % to_ZZ(comps.at(i)) << endl;
			if (to_ZZ(a) % to_ZZ(comps.at(i)) == 0) {
				// cout << "000000000";
				witnesses.at(a) = 0;
				// cout << "111111111";
				break;
			}
			else {
				// cout << "3333333333" << endl;
				// return 1 if a is a witness, 0 if not
				// Problem : when a = 2, comp = 10, cannot pass the following line. why?
				IfWitness = MillerWitness(to_ZZ(comps.at(i)), (to_ZZ(a) % to_ZZ(comps.at(i))));
				//  cout << "4444444444" << endl;
				// cout << IfWitness << endl;
				if (IfWitness != 1) {
					witnesses.at(a) = 0;
					// cout << "222222222";
					break;
				}
			}
			// if a is a reliable witness, witnesses.at(a) = 1
		}
		
		if (witnesses.at(a) == 1) {
			cout << a << " ";
		}
	}
	cout << endl;
	return; 
}

void TestFunction() {
	cout << "test function works" << endl;
}