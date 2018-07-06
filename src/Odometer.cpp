// Implementation of Odometer class
#include "../include/Odometer.h"
using namespace std;

// Constructor 1: only size specified, bases default to 10s
Odometer :: Odometer(const long& s)
{
	// get number of wheels
	number_of_wheels = s;
	// allocate memory for bases
	bases = new long[s];
	// assign bases
	for (long i=0; i<number_of_wheels; bases[i++] = 10);
	// calculate spins per cycle
	spins_per_cycle = 10 * s;
	// initialize the digits
	digits = new long[s];
	for (long i=0; i<number_of_wheels; digits[i++] = 0);
}

// Constructor 2: customized bases
//   parameter b is the vector of bases to initialize the odometer
Odometer :: Odometer(const vector<long>& b)
{
	// get the number of wheels/digits
	number_of_wheels = b.size();
	// allocate memory for bases
	bases = new long[number_of_wheels];
	// assign bases
	for (long i=0; i<number_of_wheels; ++i)
	{
		bases[i] = b.at(i);
	}
	// calculate spins per cycle, which is equal to
	// multiplication of all bases
	spins_per_cycle = b.at(0);
	for (long i=1; i<number_of_wheels; i++) {
		spins_per_cycle = spins_per_cycle * (b.at(i));
	}
	// initialize the digits
	digits = new long[number_of_wheels];
	// default digits are zeros
	for (long i=0; i<number_of_wheels; digits[i++] = 0);
}

// Get the number of digits of odometer object
long Odometer :: size() const
{
	return number_of_wheels;
}

// Get spins per cycle of the odometer object
long Odometer :: max() const
{
	return spins_per_cycle;
}

// Get certain digit
long Odometer :: get(const long& n) const
{
	return digits[n];
}

// Spin the wheels n times
void Odometer :: spin(long n)
{
	// keep track of carries on all digits
	long carry = n % spins_per_cycle;
	// temprarily store old digit
	long temp;
	// add 1 starting from last item of digits and check carries
	for (long i=number_of_wheels-1; i>=0; --i)
	{
		temp = (digits[i] + carry) % bases[i];
		carry = (digits[i] + carry) / bases[i];
		digits[i] = temp;
	}
}

void Odometer :: operator=(const Odometer& o)
{
	number_of_wheels = o.number_of_wheels;
	bases = o.bases;
	digits = o.digits;
}

ostream& operator<<(ostream& out, const Odometer& o)
{
	out << "[";
	for (long i=0; i<o.number_of_wheels-1; i++) {
		out << o.digits[i] << ", ";
	}
	out << o.digits[o.number_of_wheels-1] << "]";
	return out;
}

// Destructor
Odometer :: ~Odometer()
{
	delete [] bases;
	delete [] digits;	
}