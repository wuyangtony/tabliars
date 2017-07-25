// This program test function tony_tabliar()
#include <iostream>
#include <vector>
#include "../include/tab_liars.h"
using namespace std;

int main()
{
	cout << "Enter a composite integer: ";
	// composite n
	long n;
	cin >> n;
	// factored sieve of n
	vector<long> sieve;
	factoredSieve(n, sieve);
	// output vector of Fermat liars
	vector<long> liars;
	tony_tabliars(n, sieve, liars);
	// display the output
	cout << "Fermat liars of " << n << " are: ";
	for (long i=0; i<liars.size()-1; ++i)
	{
		cout << liars.at(i) << ", ";
	}
	cout << liars.at(liars.size()-1) << ".\n";
	return 0;
}