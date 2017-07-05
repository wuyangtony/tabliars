// Implementation of Odometer class
#include "../include/Odometer.h"
#include <iostream>


// Constructor
//   parameter b is the vector of bases to initialize the odometer
Odometer :: Odometer(const vector<long>& b) {
	// initialize the base, the base means the list of prime factor 
	bases = b;
	// get the number of wheels/digits
	number_of_wheels = b.size();
	// calculate spins per cycle, which is equal to
	// multiplication of all bases
	spins_per_cycle = b.at(0);
	for (long i=1; i<number_of_wheels; i++) {
		spins_per_cycle = spins_per_cycle * (b.at(i));
	}
	// initialize the digits
	digits.reserve(number_of_wheels);
	// default digits are zeros
	for (long i=0; i<number_of_wheels; i++) {
		digits.push_back(0);
	}
}

// Get the number of digits of odometer object
long Odometer :: size() const {
	return number_of_wheels;
}

long Odometer :: get(const long& n) const {
	return digits.at(n);
}

// Spin the wheels n times
void Odometer :: spin(long n) {
	// keep track of carries on all digits
	long carry = n % spins_per_cycle;
	// temprarily store old digit
	long temp;
	// add 1 starting from last item of digits and check carries
	for (long i=number_of_wheels-1; i>=0; i--) {
		temp = (digits.at(i) + carry) % bases.at(i);
		carry = (digits.at(i) + carry) / bases.at(i);
		digits.at(i) = temp;
	}
}

void Odometer :: operator=(const Odometer& o) {
	number_of_wheels = o.number_of_wheels;
	bases = o.bases;
	digits = o.digits;
}

ostream& operator<<(ostream& out, const Odometer& o) {
	out << "[";
	for (long i=0; i<o.number_of_wheels-1; i++) {
		out << o.digits.at(i) << ", ";
	}
	out << o.digits.at(o.number_of_wheels-1) << "]";
	return out;
}

// Destructor
Odometer :: ~Odometer() {
	bases.clear();
	digits.clear();	
}