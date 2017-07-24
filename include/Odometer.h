// This is a customized class for manipulating relative data structure
// Author: Tony Liu
// Date: Jun, 2017
#ifndef ODOMETER_H
#define ODOMETER_H
#include <vector>
#include <ostream>
using namespace std;

class Odometer {

	// Properties
private:
	long number_of_wheels; // number of digits in odometer object
	long spins_per_cycle; // number of spins from all zeros to all zeros
	vector<long> bases; // base for each digit, its size equal to size
	vector<long> digits; // current digits of odometer

	// Methods
public:
	// Constructor
	Odometer(const vector<long>& b);

	// Destructor
	~Odometer();

	// return the size of the odometer
	long size() const;

	// return spins per cycle
	long max() const;

	// get specific digit of the odometer
	long get(const long& n) const;

	// spin the wheels n times, default n = 1
	void spin(long n=1);

	// overload operator = as assignment
	void operator=(const Odometer& o);

	// overload operator << to display current digits
	friend ostream& operator<<(ostream& out, const Odometer& o);
};

#endif