/* Author:  Andrew Shallue
*  Date:  March 2014
*  Project:  Reliable witnesses
*  
*  Find the first a-strong pseudoprime, or tabulate all strong 
*  a pseudoprimes in a given interval
*/

#ifndef FIRST_LIAR_H
#define FIRST_LIAR_H

#include <NTL/ZZ.h>
#include <vector>

NTL_CLIENT


/* Finds the smallest composite integer N > a such that a is a liar for N 
  Test for witness is MillerWitness, primality is ProbPrime so be suspicious
*/
ZZ FirstSpspRandom(ZZ a);

/* Finds the smallest composite integer N such that a is a liar for N 
Instead of using a probabilistic primality test, checks primality with 
a factored sieve */
long FirstSpspFactored(ZZ a, vector<long> &factors);


#endif  //FIRST_LIAR_H
