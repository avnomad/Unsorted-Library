// mathematical functions.h: common stand-alone mathematical functions (prototypes)

#ifndef MATHEMATICAL_FUNCTIONS_H
#define MATHEMATICAL_FUNCTIONS_H

namespace Math
{
namespace MathematicalFunctions
{

	// prototypes
	unsigned long long int factorial(unsigned int n);
	unsigned long long int binomialCoefficient(unsigned int n, unsigned int k);
	double pi(double accuracy);
	double exp(double x, double accuracy);


}; // end namespace MathematicalFunctions
}; // end namespace Math

#endif // MATHEMATICAL_FUNCTIONS_H
