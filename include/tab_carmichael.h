/* Andrew Shallue, December 2013
*  
*  This file is designed to implement Pinch's algorithms for tabulating 
*  Carmichael numbers.  Ultimately I want to find sets of composites with 
*  or without a reliable witness, or with or without a reliable liar
*
*  Added to the previous project that counted strong liars of all composites
*/

#ifndef TAB_CARMICHAEL_H
#define TAB_CARMICHAEL_H

#include <NTL/ZZ.h>
#include "formulas.h"

NTL_CLIENT

/* Finds all Carmichaels with three prime factors smaller than bound
Uses method of Pinch from MathComp 1993, 61, tabulating cars up to 10^15
*/
vector< vector<long> > three_carmichael(long bound, const vector<long> &sieve);

/* simply prints a structure of the form vector< vector<long> >
*/
void print_carslist(const vector< vector<long> > &cars);

/* returns the subset of a carmichael list where all the factors are 
congruent to 3 mod 4
*/
vector< vector<long> > subset3mod4(const vector< vector<long> > &cars);


#endif //TAB_CARMICHAEL_H
