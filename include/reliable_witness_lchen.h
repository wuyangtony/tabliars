#ifndef RELIABLE_WITNESS_LCHEN_H
#define TAB_LIARS_H

#include "formulas.h"
#include <NTL/ZZ.h>
#include <NTL/RR.h>
NTL_CLIENT

/** This function is a motified version of NaiveReliableWitness. 
 * Result in the witnesses vector is a 1 if a is a reliable witness.
 * Very basic - straightforward Miller_Rabin applied for each a, each n.
 */
void NewNaiveReliableWitness(long bound, const vector<long> &comps, vector<bool> &liars);

#endif
