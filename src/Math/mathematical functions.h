// mathematical functions.h: common stand-alone mathematical functions (prototypes)

#ifndef MATHEMATICAL_FUNCTIONS_H
#define MATHEMATICAL_FUNCTIONS_H

#include <vector>
#include <stdexcept>

namespace Math
{
namespace MathematicalFunctions
{

	// prototypes
	unsigned long long int factorial(unsigned int n);
	unsigned long long int binomialCoefficient(unsigned int n, unsigned int k);
	double pi(double accuracy);	// fabs(Pi-pi(e)) < e
	double exp(double x, double accuracy); // fabs(exp(x,e) - Exp(x)) < e
											// accuracy is not significant digits!
	double BernsteinPolynomial(unsigned index, unsigned degree, double x);
	double BernsteinPolynomial(unsigned index, unsigned degree, double x, std::vector<double> &intermediate);


	/**	Code common to *Triangle classes. Not intended for client use.
	 *	This class is mostly concerned with the layout of the underlying container.
	 *	Could probably raise more functionality to the base class later.
	 */
	class BaseTriangle
	{
	protected:
		// typedefs
		typedef std::vector<unsigned long long int>::size_type size_type;

		// data members
		unsigned int nSize;	// I plan to add a way to change the size used to throw exceptions...
		unsigned int nCapacity;	// ...without throwing away already computed values. (vectors don't shrink anyway!)
		std::vector<unsigned long long int> underlyingContainer;	// C(n,k) is stored at index n*(n+1)/2 + k.
																	// this allows columns to be added/removed at the end of vector.
		// member functions
	public:
		explicit BaseTriangle(unsigned int max_n)		// BaseTriangle constructor
		{
			auto maxSupportedN = (size_type)floor((-3.0+sqrt(9.0+8.0*(underlyingContainer.max_size()-1.0)))/2.0);	// need to plot it! :)
			if(max_n > maxSupportedN)	// make sure we wont overflow when computing sizes and indices.
				throw std::length_error("max_n too large for the underlying container to store the whole triangle");

			nCapacity = nSize = max_n;
			underlyingContainer.resize((size_type)(nCapacity+1)*(nCapacity+2)>>1);	// without the test above resize would throw but 
																				// whould not give a descriptive message.
		} // end BaseTriangle constructor


		unsigned long long int operator()(unsigned int n, unsigned int k)
			throw(std::out_of_range)
		{
			if(n > nSize)
				throw std::out_of_range("n is out of range (greater than the largest value computed).");
			if(k > n)
				throw std::out_of_range("k is out of range (greater than n).");
			return underlyingContainer[((size_type)n*(n+1)>>1) + k];
		} // end function operator()

	private:
		// not copyable and not movable (yet)
		BaseTriangle(const BaseTriangle &);
		BaseTriangle(BaseTriangle &&);
		BaseTriangle &operator=(const BaseTriangle &);
		BaseTriangle &operator=(BaseTriangle &&);
	}; // end class BaseTriangle


	class PascalTriangle : public BaseTriangle
	{
	public:
		explicit PascalTriangle(unsigned int max_n = 0);	// PascalTriangle constructor
	private:
		// assumes there is at least 1 column before this one and the immediately preceding column is filled.
		// should be callable for any n > 0.
		// currently it does not check for overflow...
		// if unsigned long long is 64 bits, then for n=67 there wont be an overflow, but for n=68 there will be an overflow for 31<=k<=37.
		// maybe should add checks...
		void fillColumn(unsigned int n, size_type initial_index)	// n is column k is row
		{
			size_type begin = initial_index;
			size_type end = begin+n;
			size_type previous_begin = begin-n;

			underlyingContainer[begin++] = underlyingContainer[end--] = 1ull;
			while(begin < end)
			{
				underlyingContainer[begin++] = underlyingContainer[end--] = underlyingContainer[previous_begin] + underlyingContainer[previous_begin+1];
				++previous_begin;
			} // end while
			if(begin == end)
			{
				underlyingContainer[begin] = underlyingContainer[previous_begin] + underlyingContainer[previous_begin+1];
			} // end if
		} // end function fillColumn

	}; // end class PascalTriangle

}; // end namespace MathematicalFunctions
}; // end namespace Math

#endif // MATHEMATICAL_FUNCTIONS_H
