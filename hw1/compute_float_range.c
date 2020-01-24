#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

int main()
{
	// Note: The range of floating point numbers in C appears to be slightly larger prior to
	// being stored in a variable - e.g. I found that isfinite(1.001*a); may evaluate to true
	// but a*=1.001; isfinite(a); may evaluate to false. Results were consistent with those
	// programmed into C when the second test was done. Thus, the somewhat-awkward code below.

	FILE * F = fopen("/home/appm4650_homework/hw1/range_output.txt", "a");
	char output[100];

	// Compute largest floating point number.
	float a = 1.0; // Assume it is at least 1.0.
	float b = 0;
	while(isfinite(a))
	{
		b = a;
		a *= 10;
	}
	a = b;
	while(isfinite(a))
	{
		b = a;
		a *= 1.001;
	}
	sprintf(output, "Calculated maximum-magnitude float: %e.\n", b);
	fputs(output, F);
	sprintf(output, "Actual maximum-magnitude float: %e.\n", FLT_MAX);
	fputs(output, F);
	
	// Compute smallest-magnitude nonzero floating point number.
	a = 1.0; // Assume it is less than 1.0.
	while(a != 0.0) // Get a rough estimate.
	{
		b = a;
		a /= 10;
	}
	a = .9999*b;
	while(a	!= 0.0 && a != b) // Decrease estimate until it is within .01% of true minimum.
	{
		b = a;
		a *= .9999;
	}
	sprintf(output, "Computed minimum-magnitude floating-point number: %e.\n", b);
	fputs(output, F);
	sprintf(output, "Actual minimum-magnitude floating-point number: %e.\n", FLT_TRUE_MIN);
	fputs(output, F);
	
	// Compute machine epsilon.
	float test_value = 0.0;
	a = 1.0; // Assume it is less than 1.0.
	while(test_value != 1.0)
	{
		b = a;
		a /= 10;
		test_value = 1.0;
		test_value += a;
	}
	test_value = 0.0;
	a = b;
	while(test_value != 1.0)
	{
		b = a;
		a *= .9999;
		test_value = 1.0;
		test_value += a;
	}
	test_value = 1.0 + b;
	sprintf(output, "Computed machine epsilon: %e.\n", test_value - 1.0);
	fputs(output, F);
	sprintf(output, "Actual machine epsilon: %e.\n", FLT_EPSILON);
	fputs(output, F);

	return 0;
}
