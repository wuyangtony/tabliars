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
#include "formulas.h"

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

/* Same goal, but now the Sieve takes linear time ( O(n) ) by 
touching each composite only once */
void LinearSieveStrongTab(long a, long bound, vector<long>& ints, vector<long>& factoredsieve);

/* Tests Fermat condition by simply powering, and ProbPrime for primality.
returns a vector containing all a-Fermat psp up to and including bound */
vector<ZZ> TrivialFermatTab(ZZ a, ZZ bound);


#endif //TAB_PSP_H

