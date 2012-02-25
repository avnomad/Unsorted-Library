// mathematical functions.cpp:  common stand-alone mathematical functions (implementation)

#include "mathematical functions.h"

namespace Math
{
namespace MathematicalFunctions
{

	unsigned long long int factorial(unsigned int n)
	{
		unsigned long long int product = 1;

		while(n>1)
			product *= n--;

		return product;
	} // end function factorial


	unsigned long long int binomialCoefficient(unsigned int n, unsigned int k)
	{
		unsigned long long int numerator = 1; // TODO: currently it can overflow even if the result can fit...
		unsigned long long int denominator = 1;	// ...into the return type. Need to fix that.

		if( n - k < k) k = n - k;

		while(k)
		{
			numerator *= n--;
			denominator *= k--;
		}

		return numerator / denominator;
	} // end function binomialCoefficient


	double pi(double accuracy)	// extremely slow convergence!!!
	{
		double sum = 4, p;
		unsigned int c = 1;

		//accuracy = fabs(accuracy);
		for(;;)
		{
			sum -= p = (double)4 / (c+=2);
			if(p < accuracy) return sum;
			sum += p = (double)4 / (c+=2);
			if(p < accuracy) return sum;
		} // end for
	} // end function pi


	double exp(double x, double accuracy)	// is this the best way to implement this?
	{
		double sum;
		double p;
		unsigned int i;

		sum = 1 + x;
		p = x;
		i = 2;
		//accuracy = fabs(accuracy);
		do
		{
			p *= x / i++;
			sum += p;
		}
		while(p>accuracy);

		return sum;
	} // end function exp

}; // end namespace MathematicalFunctions
}; // end namespace Math
