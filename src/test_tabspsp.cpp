// Author: Tony Liu
// This is a program to test different method of tabulating strong pseudoprimes
#include <ctime>
#include <vector>
#include <NTL/ZZ.h> 
#include <NTL/RR.h>
#include "../include/formulas.h"
#include "../include/tab_psp.h"
using namespace std;

int main() {
	
	long n, a;
	cout << "Enter a positive integer as the bound:" << endl;
	cin >> n;
	vector<long> f;
	cout << "Creating a factored sieve up to " << n << "....\n";
	factoredSieve(n, f);
	cout << "Factored sieve created." << endl;
	vector<long> ints; // vector of indicators of strong pseudoprimes
	ints.reserve(n+1);
	cout << "Now enter a positive integer as the base:" << endl;
	cin >> a;
	clock_t duration; // used for timing

	vector<long> spsp; // vector that stores all strong pseudprimes

	cout << "Choose an algorithm:" << endl;
	cout << " 1) Original   2) Paper   3) Tony's " << endl;
	int method;
	cin >> method;

	while (true) {
		if (method == 1) {
			duration = clock();
			SieveStrongTab(a, n, ints, f);
			duration = clock() - duration;
			break;
		}
		else if (method == 2) {
			duration = clock();
			SieveStrongTabOnPaper(a, n, ints, f);
			duration = clock() - duration;
			break;
		}
		else if (method == 3) {
			duration = clock();
			SieveStrongTabByTony(a, n, ints, f);
			duration = clock() - duration;
			break;
		}
		else {
			cout << "Please choose either 1, 2 or 3." << endl;
		}
	}

	for (long i=0; i<=n; i++) {
		if (ints.at(i) == 1) {
			spsp.push_back(i);
		}
	}

	double result = ((double)duration) / CLOCKS_PER_SEC;
	// Output the result of timing
	cout << "It takes " << result << " seconds with method " << method << ".\n";
}