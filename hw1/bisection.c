#include <stdio.h>
#include <assert.h>
#include <math.h>

#define A_INIT 1.0
#define B_INIT 2.0
#define N_ITER 10

float f(float x) // The function for which to find a root.
{
	return x*x - 2;
}

void iterate_bisection(float (*f)(float), float *a, float *b)
{ 	// Executes an iteration of the bisection method and modifies endpoints in place.
	  // *f: pointer to a function f:R->R for which to find a root.
	  // *a: pointer to the left endpoint.
	  // *b: pointer to the right endpoint.
	float p = .5*(*a + *b);
	if((*f)(p) == 0) // An exact solution has been found.
	{
		*a = p;
		*b = p;
		return;
	}
	else if(((*f)(*a)) * ((*f)(p)) > 0) // f(a) and f(p) have the same sign
		*a = p;
	else if (((*f)(*b)) * ((*f)(p)) > 0) // f(b) and f(p) have the same sign
		*b = p;
	else // Something has gone wrong.
		assert(0);
}

int main()
{	
	float a = A_INIT;
	float b = B_INIT;

	for(int i=0; i<N_ITER; i+=1)
	{
		iterate_bisection(&f, &a, &b);
		printf("Iteration %d: answer is in (%f, %f).\n", i+1, a, b);
	}

	printf("Final approximation: %f.\n", .5*(a + b));
	printf("Actual answer: %f.\n", sqrt(2));
	printf("Absolute error: %f.\n", fabs(sqrt(2) - .5*(a + b)));
	printf("Relative error: %f.\n", fabs(sqrt(2) - .5*(a + b))/sqrt(2));

	return 0;
}
