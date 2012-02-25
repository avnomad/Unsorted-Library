//mathClass.h: Math calss interface
//mathematical functions

#ifndef _mathClass_
#define _mathClass_

class Math
{
public:
	unsigned int factorial(unsigned int n);
	unsigned int binomialCoefficient(unsigned int n, unsigned int k);
	double pi(double accuracy);
	double exp(double x, double accuracy);
};

#endif
