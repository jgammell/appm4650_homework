#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>

int main()
{
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
	printf("Calculated maximum-magnitude float: %e.\n", b);
	printf("Actual maximum-magnitude float: %e.\n", FLT_MAX);

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
	printf("Computed minimum-magnitude floating-point number: %e.\n", b);
	printf("Actual minimum-magnitude floating-point number: %e.\n", FLT_TRUE_MIN);

	// Compute machine epsilon.
	a = 1.0; // Assume it is less than 1.0.
	while(a+1 != 1)
	{
		b = a;
		a /= 10;
	}
	a = b;
	float test_value = 1.0;
	while(test_value != 1.0)
	{
		b = a;
		a *= .9999;
		test_value += a;
	}
	printf("Computed machine epsilon: %e.\n", a);
	printf("Actual machine epsilon: %e.\n", FLT_EPSILON);

	return 0;
}
