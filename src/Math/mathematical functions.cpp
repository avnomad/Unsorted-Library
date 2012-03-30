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


	/* uses constant space */
	unsigned long long int binomialCoefficient(unsigned int n, unsigned int k)
	{											// should use inline assembly to check for overflow efficiently...
		unsigned long long result = n;
		unsigned long long denom = 2ull;

		if(n - k < k) k = n - k;	// k = min(k,n-k)
		if(k == 0u) return 1ull;
		if(k == 1u) return n;

		result *= --n; /* can't overflow because at this point result==n and n is 32-bit */

		auto i = 3u;
		while(i <= k)
		{
			--n;
			if(numeric_limits<decltype(result)>::max()/n < result)	// if it would overflow
			{
				result /= denom;
				if(numeric_limits<decltype(result)>::max()/n < result)	// if it would overflow
					goto divide_first;
				result *= n;
				denom = i++;
				continue;
			} // end if
			result *= n;
			denom *= i++;
		} // end while

		/* at this point i > k */
		return result/denom; /* at this point denom != 1 and remainder will be 0 */

		do	/* if I need to divide first once I will always need to divide first */
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
		}
		while(i <= k);

		return result;	/* at this point denom is no longer valid but if it was it would be 1 */
	} // end function binomialCoefficient


	double pi(double accuracy)	// extremely slow convergence!!!
	{
		double sum = 4, p;
		unsigned int c = 1;

		//accuracy = fabs(accuracy);
		if(accuracy < 3*numeric_limits<double>::epsilon())	// if I am correct, there is no point trying to add
			accuracy = numeric_limits<double>::epsilon();	// something smaller than that to an approximation of Pi...
		for(;;)
		{
			sum -= p = 4.0 / (c+=2);
			if(p < accuracy) return sum;
			sum += p = 4.0 / (c+=2);
			if(p < accuracy) return sum;
		} // end for
	} // end function pi


	double exp(double x, double accuracy)	// is this the best way to implement this?
	{
		double oldSum;
		double newSum;
		double p;
		unsigned int i;

		if(x < 0)	// workaround to cope with arithmetic errors when computing exp with x < 0.
		{
			if(accuracy > 1/-x) accuracy = 1/-x;	// accuracy = min(accuracy,1/x)
			return 1.0/exp(-x,accuracy*x*x/2.0);	// if my calculations are correct, new accuracy guarantees that
													// fabs(return_value-Exp(x)) < old_accuracy
		} // end if

		newSum = 1 + x;
		p = x;
		i = 2;
		//accuracy = fabs(accuracy);
		do
		{
			oldSum = newSum;
			p *= x / i++;
			newSum = p + oldSum;
		}
		while(p>accuracy && newSum != oldSum);

		return newSum;
	} // end function exp


	/* proxy function. Allocates memory and calls BernsteinPolynomial/4 to do the real job */
	double BernsteinPolynomial(unsigned index, unsigned degree, double x)
	{
		std::vector<double> intermediate(index+1);

		return BernsteinPolynomial(index,degree,x,intermediate);
	} // end function BernsteinPolynomial


	/* Compute the value of one Bernstein polynomial. */
	/* assumes 0 <= index <= degree && degree >= 0 */
	double BernsteinPolynomial(unsigned index, unsigned degree, double x, std::vector<double> &intermediate)
	{
		/* during the nth pass intermediate[c] holds B[c,n+c] */
		/* size == index+1 throughout */
		double cx = 1.0 - x;

		intermediate[0] = 1.0;
		for(auto i = 1u ; i <= index ; i++)
			intermediate[i] = x*intermediate[i-1];

		for(auto i = 1u ; i <= degree-index ; i++)
		{
			intermediate[0] = cx*intermediate[0];
			for(auto j = 1u ; j <= index ; j++)
				intermediate[j] = cx*intermediate[j] + x*intermediate[j-1];
		} // end for

		return intermediate[index];
	} // end function BernsteinPolynomial


	PascalTriangle::PascalTriangle(unsigned int max_n)
		:BaseTriangle(max_n)
	{
		if(numeric_limits<BaseTriangle::element_type>::digits == 64 && max_n >= 68u)	// if n is 67 everything fits. if n is 68 k in 31..37 overflows...
			throw std::domain_error("At least one binomial coefficient could not fit into an unsigned long long when creating PascalTriangle.");
					// should add more tests in case unsigned long long is different size...

		// fill the underlying container
		underlyingContainer[0] = 1ull;
		size_type index = 1u;
		for(unsigned int n = 1u ; n <= nCapacity ; index += ++n)
			fillColumn(n,index);
	} // end PascalTriangle constructor


	BernsteinTriangle::BernsteinTriangle(double x, unsigned int max_n)
		:BaseTriangle(max_n)
	{
		this->x = x;

		// fill the underlying container
		underlyingContainer[0] = 1.0;
		size_type index = 1u;
		for(unsigned int n = 1u ; n <= nCapacity ; index += ++n)
			fillColumn(n,index);
	} // end BernsteinTriangle constructor

}; // end namespace MathematicalFunctions
}; // end namespace Math
