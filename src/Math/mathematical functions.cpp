// mathematical functions.cpp:  common stand-alone mathematical functions (implementation)

#include "mathematical functions.h"
#include <math.h>
using std::sqrt;
using std::floor;
#include <limits>
using std::numeric_limits;

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
	{											// should use inline assembly to check for overflow efficiently...
		unsigned long long result = n;
		unsigned long long denom = 1ull;

		if(n - k < k) k = n - k;
		if(k == 0) return 1;

		auto i = 2u;
		while(i <= k)
		{
			--n;
			if(numeric_limits<decltype(result)>::max()/n < result)	// if it would overflow
			{
				result /= denom;
				if(numeric_limits<decltype(result)>::max()/n < result)	// if it would overflow
				{
					denom = 1ull;
					goto divide_first;
				} // end if
				denom = i++;
				result *= n;
				continue;
			} // end if
			result *= n;
			denom *= i++;
		} // end while
		while(i <= k)
		{
			--n;
		divide_first:
			unsigned long long remainder = result%i;
			result /= i;	// first divide
			if(numeric_limits<decltype(result)>::max()/n < result)	// if it would overflow
				throw std::domain_error("binomialCoefficient cannot fit into an unsigned long long");
			result *= n;	// then multiply
			if(remainder != 0)
			{
				remainder *= n;
				remainder /= i;
				if(numeric_limits<decltype(result)>::max() - result < remainder)	// if it would overflow
					throw std::domain_error("binomialCoefficient cannot fit into an unsigned long long");
				result += remainder;
			} // end if
			++i;
		} // end while

		return (denom != 1ull) ? result/denom : result;
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


	PascalTriangle::PascalTriangle(unsigned int max_n)
	{
		 auto maxSupportedN = (size_type)floor((-3.0+sqrt(9.0+8.0*(underlyingContainer.max_size()-1.0)))/2.0);	// need to plot it! :)
		 if(max_n > maxSupportedN)	// make sure we wont overflow when computing sizes and indices.
			 throw std::length_error("max_n too large for the underlying container to store the whole triangle");

		 nCapacity = nSize = max_n;
		 underlyingContainer.resize((size_type)(nCapacity+1)*(nCapacity+2)>>1);	// without the test above resize would throw but 
																				// whould not give a descriptive message.
		 // fill the underlying container
		 underlyingContainer[0] = 1ull;
		 size_type index= 1u;
		 for(unsigned int n = 1u ; n <= nCapacity ; index += ++n)
			 fillColumn(n,index);
	} // end PascalTriangle constructor

}; // end namespace MathematicalFunctions
}; // end namespace Math
