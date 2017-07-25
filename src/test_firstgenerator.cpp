#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	long n;
	cout << "Enter an integer: ";
	cin >> n;
	clock_t duration; // used for timing
	duration = clock();
	long generator = firstGenerator(n);
	duration = clock() - duration;
	if (generator == n)
	{
		cout << "There exists no generator for multiplicative group mod " << n << endl;
	}
	else
	{
		cout << "The first generator for multiplicative group mod " << n << " is " << generator << endl;
	}
	double result = ((double)duration) / CLOCKS_PER_SEC;
	// Output the result of timing
	cout << "It takes " << result << " seconds to finish all this work.\n";
	return 0;
}