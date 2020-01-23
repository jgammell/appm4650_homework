#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

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
	FILE * F = fopen("/home/appm4650_homework/hw1/bisection_output.txt", "a");
	
	float a = 1.0; // initial interval
	float b = 2.0;

	for(int i=0; i<10; i+=1) // run 10 iterations of algorithm
	{
		iterate_bisection(&f, &a, &b);
		char output[50];
		sprintf(output, "Iteration %d: answer is in (%f, %f).\n", i+1, a, b);
		fputs(output, F);
	}
	
	char output[50];
	sprintf(output, "Final approximation: %f.\n", .5*(a + b));
	fputs(output, F);
	sprintf(output, "Actual answer: %f.\n", sqrt(2));
	fputs(output, F);
	sprintf(output, "Absolute error: %f.\n", fabs(sqrt(2) - .5*(a + b)));
	fputs(output, F);
	sprintf(output, "Relative error: %f.\n", fabs(sqrt(2) - .5*(a + b))/sqrt(2));
	fputs(output, F);
	
	return 0;
}
