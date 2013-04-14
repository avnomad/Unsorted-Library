//	Copyright (C) 2009-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Unsorted Library.
 *
 *	Unsorted Library is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Unsorted Library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Unsorted Library.  If not, see <http://www.gnu.org/licenses/>.
 */

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