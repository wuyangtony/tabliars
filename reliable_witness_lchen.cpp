#include "reliable_witness_lchen.h"

/** This function is a modified version of Andrew's NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<bool> &witnesses) {
	// initialize output vector
	witnesses.reserve(bound);
        long IfWitness = 0;  // 1 means a is a witness for a given composite n
	
	for (long i=0; i < bound; i++) {
		witnesses.push_back(1);
	}

	for (long a=0; a < bound; a++) {
		for (long i = 0; i < comps.size(); i++) {
			// apply miller-rabin test
			// if a % i = 0, then a is neither a strong witness nor a strong liar
			if (to_ZZ(a) % to_ZZ(comps.at(i)) == 0) {
				witnesses.at(a) = 0;
			}
			else {
				// return 1 if a is a witness, 0 if not
				IfWitness = MillerWitness(to_ZZ(comps.at(i)), (to_ZZ(a) % to_ZZ(comps.at(i))));
				if (IfWitness != 1) {
					witnesses.at(a) = 0;
				}
			}
		}
	}
	return; 
}
