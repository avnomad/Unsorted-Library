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
	 */
	template<typename ElementType>
	class BaseTriangle
	{
	protected:
		// typedefs
		typedef ElementType element_type;
		typedef typename std::vector<element_type>::size_type size_type;

		// data members
		unsigned int nSize;	// I plan to add a way to change the size used to throw exceptions...
		unsigned int nCapacity;	// ...without throwing away already computed values. (vectors don't shrink anyway!)
		std::vector<element_type> underlyingContainer;	// C(n,k) is stored at index n*(n+1)/2 + k.
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


		element_type operator()(unsigned int n, unsigned int k)
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


	class PascalTriangle : public BaseTriangle<unsigned long long int>
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


	class BernsteinTriangle : public BaseTriangle<double>
	{
		// data members
		double x;
	public:
		explicit BernsteinTriangle(double x, unsigned int max_n = 0);	// BernsteinTriangle constructor
	private:
		// assumes there is at least 1 column before this one and the immediately preceding column is filled.
		// should be callable for any n > 0.
		// currently it does not check for overflow...
		void fillColumn(unsigned int n, size_type initial_index)	// n is column k is row
		{
			size_type begin = initial_index;
			const size_type end = begin+n;
			size_type previous_begin = begin-n;
			const double cx = 1.0 - x;
			double left_term;

			underlyingContainer[begin++] = cx*underlyingContainer[previous_begin];
			left_term = x*underlyingContainer[previous_begin];
			while(begin < end)
			{
				underlyingContainer[begin++] = left_term + cx*underlyingContainer[++previous_begin];
				left_term = x*underlyingContainer[previous_begin];
			} // end while
			underlyingContainer[end] = left_term;
		} // end function fillColumn

	}; // end class BernsteinTriangle

}; // end namespace MathematicalFunctions
}; // end namespace Math

#endif // MATHEMATICAL_FUNCTIONS_H
