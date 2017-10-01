// This is a customized class for manipulating relative data structure
// Author: Tony Liu
// Date: Jun, 2017
#ifndef ODOMETER_H
#define ODOMETER_H
#include <ostream>
#include <vector>

/*
	Odometer appears mostly in cars. Basically we can think of any natural
	number as an odometer with 10s as bases for all digits.
	The main difference for my Odometer class is that it accepts different
	bases for each individual digit, and the number of digits stay constant.
*/
class Odometer {

	// Properties
private:
	long number_of_wheels; // number of digits in odometer object
	long spins_per_cycle; // number of spins from all zeros to all zeros
	long *bases; // base for each digit, its size equal to size
	long *digits; // current digits of odometer

	// Methods
public:
	// Constructor 1: only specify size
	Odometer(const long& s);

	// Constructor 2: with a vector
	Odometer(const vector<long>& b);

	// Destructor
	~Odometer();

	// return the size of the odometer
	long size() const;

	// return number of spins in a cycle
	long max() const;

	// get specific digit of the odometer
	long get(const long& n) const;

	// spin the wheels n times, default n = 1
	void spin(long n=1);

	// overload operator = as assignment
	void operator=(const Odometer& o);

	// overload operator == for equality check
	void operator==(const long& n);

	// overload operator != for inequality check
	void operator!=(const long& n);

	// overload operator << to display current digits
	friend ostream& operator<<(ostream& out, const Odometer& o);
};

#endif