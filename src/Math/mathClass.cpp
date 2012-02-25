//mathClass.cpp: Math calss implementation
//mathematical functions

#include "mathClass.h"
#include <iostream>
unsigned int Math::factorial(unsigned int n)
{
	unsigned int product = 1;
	
	while(n>1)
	    product *= n--;
	    
	return product;
}

unsigned int Math::binomialCoefficient(unsigned int n, unsigned int k)
{
	unsigned int numerator = 1;
	unsigned int denominator = 1;
	
	if( n - k < k) k = n - k;
	
	while(k)
	{
		numerator *= n--;
		denominator *= k--;
	}
	
	return numerator / denominator;
}

double Math::pi(double accuracy)// extremely slow convergence!!!
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
	}
}

double Math::exp(double x, double accuracy)
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
}
