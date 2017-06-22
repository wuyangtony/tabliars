#include "../include/Odometer.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
	cout << "Let's create a vector first." << endl;
	cout << "Enter the size of the vector: " << endl;
	long size;
	cin >> size;
	vector<long> v;
	v.reserve(size);
	cout << "An empty vector v of size " << size << " is created.";
	cout << "Now for each element of v, randomly choose an integer between 2 and 20 to fill in, ";
	cout << "and v will be the bases for the odometer." << endl;
	for (long i=0; i<size; i++) {
		v.push_back(rand()%19 + 2);
	}
	cout << "Vector v filled with random numbers." << endl;
	cout << "They are: ";
	for (int i=0; i<v.size()-1; i++) {
		cout << v.at(i) << ", ";
	}
	cout << v.at(v.size()-1) << endl;
	cout << "Now let's create an odometer o with v." << endl;
	Odometer o(v);
	cout << "Odometer o created." << endl;
	cout << "Now testing...." << endl;
	cout << "First test: all initial digits of o" << endl;
	cout << o << endl;
	cout << "Second test: spin the odometer" << endl;
	while (true) {
		cout << "Enter the number of spins you want(0 means quit): ";
		long s;
		cin >> s;
		if (s == 0) break;
		o.spin(s);
		cout << "Odometer o after spin is " << o << endl;
	}
	return 0;
}