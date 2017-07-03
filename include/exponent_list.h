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
vector<long> CompsGen(vector<vector<long> > &exp_list, const vector<long> &bases);
void CompsGen2(const vector<vector<long> > &exps_list, const vector<long> &comp_bases, vector<long> &comps_list);
void OdometerGen(const vector<long> &exponents, const vector<long> &comp_bases, vector<long> &comps_set);
void BoundGen2(vector<long> &expo_gen, const vector<long> &comp_bases, long exponent);

#endif