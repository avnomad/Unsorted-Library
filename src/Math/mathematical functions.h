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
	double pi(double accuracy);
	double exp(double x, double accuracy);

	class PascalTriangle
	{
		// typedefs
		typedef std::vector<unsigned long long int>::size_type size_type;

		// data members
		unsigned int nSize;	// I plan to add a way to change the size used to throw exceptions...
		unsigned int nCapacity;	// ...without throwing away already computed values. (vectors don't shrink anyway!)
		std::vector<unsigned long long int> underlyingContainer;	// C(n,k) is stored at index n*(n+1)/2 + k.
																	// this allows columns to be added/removed at the end of vector.
		// member functions
	public:
		explicit PascalTriangle(unsigned int max_n = 0);	// PascalTriangle constructor
		~PascalTriangle(){/* empty */}	// ~PascalTriangle destructor

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
		// assumes there is at least 1 column before this one and the immediately preceding column is filled.
		// should be callable for any n > 0.
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

		// not copyable and not movable (yet)
		PascalTriangle(const PascalTriangle &);
		PascalTriangle(PascalTriangle &&);
		PascalTriangle &operator=(const PascalTriangle &);
		PascalTriangle &operator=(PascalTriangle &&);
	}; // end class PascalTriangle

}; // end namespace MathematicalFunctions
}; // end namespace Math

#endif // MATHEMATICAL_FUNCTIONS_H
