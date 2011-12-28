#ifndef DIVIDEBYZEROEXCEPTION_H
#define DIVIDEBYZEROEXCEPTION_H

#include <stdexcept>
#include <string>

class DivideByZeroException : public std::logic_error
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline DivideByZeroException(const std::string &description)									// DivideByZeroException default constructor
		:logic_error(description)
	{
		// empty body
	} // end DivideByZeroException default constructor


	inline ~DivideByZeroException()															// DivideByZeroException destructor
	{
		// empty body
	} // end DivideByZeroException destructor




	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/

private:

	/***************
	* data members *
	***************/

}; // end class DivideByZeroException

#endif // DIVIDEBYZEROEXCEPTION_H