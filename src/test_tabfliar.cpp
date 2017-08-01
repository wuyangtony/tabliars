// This program test function tony_tabliar()
#include <iostream>
#include <vector>
#include <ctime>
#include "../include/tab_liars.h"
using namespace std;

int main()
{
	// for timing
	clock_t duration;
	double t;
	cout << "Enter a composite integer: ";
	// composite n
	long n;
	cin >> n;
	// factored sieve of n
	vector<long> sieve;
	// test tony's implementation
	vector<long> liars;
	duration = clock();
	factoredSieve(n, sieve);
	tony_tabliars(n, sieve, liars);
	duration = clock() - duration;
	t = double(duration) / CLOCKS_PER_SEC;
	t *= 1000;
	// display the output
	/*
	cout << "Fermat liars of " << n << " are: ";
	for (long i=0; i<liars.size()-1; ++i)
	{
		cout << liars.at(i) << ", ";
	}
	cout << liars.at(liars.size()-1) << ".\n";*/
	cout << "It takes " << t << " miliseconds to finish Tony's implementation.\n";
	liars.clear();
	duration = clock();
	brute_tabliars(n, liars);
	duration = clock() - duration;
	t = double(duration) / CLOCKS_PER_SEC;
	t *= 1000;
	/*
	cout << "Fermat liars of " << n << " are: ";
	for (long i=0; i<liars.size()-1; ++i)
	{
		cout << liars.at(i) << ", ";
	}
	cout << liars.at(liars.size()-1) << ".\n";*/
	cout << "It takes " << t << " miliseconds to finish brute force.\n";
	return 0;
}