#include "../include/reliable_witness_lchen.h"
#include <vector>
#include <iostream>
#include <fstream>


/** This function is a modified version of Andrew's NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<long> &witnesses, bool &ifreliable, long &count_wit) {
	witnesses.clear();
    long IfWitness;

	// cout << "test naive reliable witness comps.size() : " << comps.size() << endl;

    // if reliable is a vector that indicate whether or not this comps have reliable witness. 
    // 
	ifreliable = 0;

	// initialize output vector
	// update: we don't need to use a vector to save the witness

	// check_wit is an object to check if a base is a reliable witness. 
	// for each base (in each for loop), set to 1, 
    // if it is not a witness for a comp, then it is not a reliable witness
	// then change it to 0.
    long check_wit;

    // update: we want to count the number of reliable witnesses for a given comps set.
    // need a long object to track the number.
    count_wit = 0;

	// witnesses.reserve(bound);

 //    long IfWitness = 0;  // 1 means a is a witness for a given composite n
	// for (long i = 0; i < bound; i++) {
	// 	//cout << "allocate vector" << endl; 
	// 	witnesses.push_back(1);
	// }

	// when a = 0, the program cannot enter the inner for loop. 
	for (long a = 1; a < bound; a++) {
        check_wit = 1; // assume a is a reliable witness 
		//cout << "comps.size()" << comps.size() << endl;
		for (long k = 0; k < comps.size(); k++) { 
			// apply miller-rabin test
			// if a % i = 0, then a is neither a strong witness nor a strong liar
            // for all k, if a is a witness，then it is a reliable witness
			if (to_ZZ(a) % to_ZZ(comps.at(k)) == 0) {
				// witnesses.at(a) = 0;
                // a is not a reliable witness, change it to 0
                check_wit = 0;
				break;
			}
			else {
				// Note that MillerWitness only supports odd composits 
				IfWitness = MillerWitness(to_ZZ(comps.at(k)), (to_ZZ(a) % to_ZZ(comps.at(k))));
                // if a is not a MillerWitness, change check_wit to 0
				if (IfWitness != 1) {
					// witnesses.at(a) = 0;
                    check_wit = 0;
					break;
				}
			}
			// if a is a reliable witness, check_wit = 1
		}

		if (check_wit == 1) {
			//cout << a << " is a reliable witness for the set of composite. Increase the bound.." << endl;
			//ifreliable.at(0) = 1;
			witnesses.push_back(a);
            count_wit++;            
		}
	}

    if (count_wit > 0) {
        ifreliable = 1;
        cout << "there are " << count_wit << " reliable witnesses for this composite set. " << endl;
        cout << "the count_wit is " << count_wit << " , the bound is " << bound << endl;
        double percentage = double(count_wit)/double(bound) * 100;

        cout << "the percentage of reliable witness up to bound is " << percentage << "%." <<endl; 

        cout << "the reliable witnesses are";
        for (int i = 0; i < witnesses.size(); i++) {
        	cout << witnesses.at(i) << " ";
        }
        cout << endl;
    }
    else {
    	ifreliable = 0;
        cout << "there are no reliable witness for the composite set." << endl;
    }

	//cout << endl;
	return; 
}
