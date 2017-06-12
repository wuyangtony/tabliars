/* tab_psp.h
Author:  Andrew Shallue
Date:  July 2015
Purpose: implement algorithms for tabulating fermat and strong pseudoprimes
from my "Tabulating pseudoprimes and tabulating liars " paper
*/

#ifndef TAB_PSP_H
#define FIRST_LIAR_H

#include <NTL/ZZ.h>
#include <vector>
#include <unordered_map>
#include "formulas.h"
#include "DoubleLinkedListArray.h"

NTL_CLIENT

/* Uses NTL's MillerWitness to return the strong pseudoprimes to the base 
a.  Note that ProblPrime used to test compositeness, so might make mistakes*/
vector<ZZ> TrivialStrongTab(ZZ a, ZZ bound);

/* Same goal, but now use original algorithm in the paper with 
an O(n loglog n) complexity.  So no fancy sieve techniques
Output: ints will be modified so that 1 at index i means i is a strong 
pseudoprime to the base a.  Requires a factored sieve.
*/
void SieveStrongTab(long a, long bound, vector<long>& ints, vector<long>& factoredsieve);

/* A new algorithm relecting the 4th major revise on paper with 
prime powers and multiplicative orders
*/
void SieveStrongTabOnPaper(long a, long bound, vector<long>& P, vector<long>& factoredsieve);

/************************************************************************* 
 *A new implementation of the above, reflecting Tony's own revision*/
void SieveStrongTabByTony(long a, long bound, vector<long>& ints, vector<long>& factoredsieve);
//************************************************************************

/* Tests Fermat condition by simply powering, and ProbPrime for primality.
returns a vector containing all a-Fermat psp up to and including bound */
vector<ZZ> TrivialFermatTab(ZZ a, ZZ bound);

/* Applies a wheel to speed up the sieve for Fermat psp
*/
vector<ZZ> WheelFermatTab(long a, long bound, vector<long>& factoredsieve);

/* A linear sieve technique for tabulating Fermat pseudoprimes.
Uses the DoubleLinkedListArray for contast time deletions

Note!  Does not work!  In fact, whole idea might be flawed.  See README
*/
vector<long> LinearSieveFermatTab(long a, long bound, vector<long>& factoredsieve);

/* Returns the set F(q) for a linear sieve strategy for tabulating Fermat psp
F(q) = {3 <= f <= n | gcd(q,n)=1, for r < q, r nmid f or f = 1 mod r\ell_a(r)}
*/
vector<long> FermatSieveF(long p, long e, long n, long a);

#endif //TAB_PSP_H

