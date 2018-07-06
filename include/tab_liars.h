/* Andrew Shallue, December 2013
*
* Tracking witnesses and liars with respect to a given set of composites
* Inspired by a question of Pomerance:  is there an a that is a witness
* for every member of the set?  Also interesting:  is there an a that is 
* a liar for every member of the set?
*/

#ifndef TAB_LIARS_H
#define TAB_LIARS_H

#include <NTL/ZZ.h>
#include <vector>
#include <cmath>
#include "formulas.h"
#include "Odometer.h"

NTL_CLIENT

/*
This is Tony's implementation of tabulating Fermat liars by constructing
subset of multiplicative group modulo n.
@para	n: 	   a composite integer whose Fermat liars are sought
		sieve: a vector of factored sieve of n
		liars: see return
@return	void, but liars is passed by reference, which stores the outputs
*/
void tony_tabliars(const long& n, const vector<long>& sieve, vector<long>& liars);

/*
The brute force method of finding Fermat liars.
@para	n: 	   a composite integer whose Fermat liars are sought
		liars: see return
@return	void, but liars is passed by reference, which stores the outputs
*/
void brute_tabliars(const long&n, vector<long>& liars);

/*
The brute force method of finding strong liars.
@para	n: 	   a composite integer whose strong liars are sought
		liars: see return
@return	void, but liars is passed by reference, which stores the outputs
*/
void brute_tabstrongliars(const long&n, vector<long>& liars);

/* the vector comps is a list of factored carmichael numbers
Thm: a strong liar iff (a|p) matches for all p dividing n
so this program simply checks that 
Output is the liars vector, 1 if a liar for all comps
*/
void naive_tabliars(long bound, const vector< vector<long> > &comps, vector<bool> &liars);

/* the vector comps can be an list of factored composite numbers here.
result in the witnesses vector is a 1 if a is a reliable witness
Very basic - straightforward Miller_Rabin applied for each a, each n
*/
void NaiveReliableWitness(long bound, const vector< vector<long> > &comps, vector<bool> &witnesses);

/* a subprogram that returns 1 if a is a liar for n
requires n to be a factored carmichael number, uses theorem stated above.
*/
bool IsCarLiar(long a, const vector<long> &n);

/* a sieving style search for a reliable witness.  Currently the composites 
must be factored and must be Carmichael numbers 
*/
void SieveReliableWitness(long bound, const vector< vector<long> > &comps, vector<bool> &witnesses, const vector<long> &factors);

/* this subprogram returns 1 if a is a liar for n, but now n can be any odd
composite.  Thm from Alford, Granville, Pomerance:  a is a strong liar for n
iff a^(n-1) = 1 mod n and there exists k so that 2^k || l_a(p) for all p | n.
Important that n is given as a sequence of prime factors - it will not be checked
We'll also assume n is carmichael, and do it for all a up to some bound.
*/
void IsLiarOrd2(long bound, const vector<long> &n, vector<bool> &liars, const vector<long> &factors);

/* subroutine.  Given a vector of longs and prime p, changes the vector so that 
entry i contains i^d mod p. 
The vector factors is a result of an earlier sieve factoring call.  */
void PowerAll(long bound, vector<long> &A, long d, long p, const vector<long> &factors);

/* print the entries of a vector<bool> that are 1 */
void PrintOnes(const vector<bool> &input);



#endif // TAB_LIARS_H
