#ifndef RELIABLE_WITNESS_LCHEN_H
#define RELIABLE_WITNESS_LCHEN_H

#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>

NTL_CLIENT

/** This function is a motified version of NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<long> &witnesses, vector<bool> &ifreliable, long &count_wit);

#endif
