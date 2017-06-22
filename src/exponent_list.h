#ifndef EXPONENTS_LIST_H
#define EXPONENTS_LIST_H

#include <NTL/ZZ.h>
#include <NTL/RR.h>
NTL_CLIENT

/** This function is a motified version of NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
vector<vector<long> > ExponentList(const vector<long> &exponents);
#endif