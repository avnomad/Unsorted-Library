#ifndef TRIPLE_H
#define TRIPLE_H

template<typename T1 , typename T2 , typename T3>
struct Triple
{
	// typedefs
	typedef T1 first_type;
	typedef T2 second_type;
	typedef T3 third_type;

	// constructors
	Triple()																		// default constructor
	{
		// empty body (the default constructors
		// for the data members will be called)
	} // end Triple default constructor

	template<typename O1 , typename O2 , typename O3> // other (compatible) type
	Triple(const Triple<O1,O2,O3> &original)										// copy constructor
		:first(original.first),second(original.second),third(original.third)
	{
		// empty body
	} // end Triple copy constructor

	Triple(const T1 &firstValue , const T2 &secondValue , const T3 &thirdValue)		// constructor
		:first(firstValue),second(secondValue),third(thirdValue)
	{
		// empty body
	} // end Triple constructor

	// operators
	Triple &operator=(const Triple&original)										// operator =
	{
		first = original.first;
		second = original.second;
		third = original.third;
		return *this;
	} // end fuction operator =

	// data members
	T1 first;	// the first stored value
	T2 second;	// the second stored value
	T3 third;	// the third stored value
}; // end class Triple

#endif // TRIPLE_H
	