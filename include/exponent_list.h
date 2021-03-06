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
void OdometerGen(const vector<long> &exponents, const vector<long> &comp_bases, vector<long> &comps_set, vector<int> &prev_height);
void BoundGen2(vector<long> &expo_gen, const vector<long> &comp_bases, long exponent);
void Gen_New_bound(long &new_bound, const vector<long> &comp_bases, long first_i_spsp, long bound);


#endif