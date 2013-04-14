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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

class ExceptionExtension
{
public:
	typedef const std::string &csr;

	/***************************
	* contructors & destructor *
	***************************/

	ExceptionExtension(csr library , csr function , csr description)								// ExceptionExtension constructor
		:iFunction(function),iLibrary(library),iDetails(description)
	{
		// empty body
	} // end ExceptionExtension constructor


	ExceptionExtension(const ExceptionExtension &original)											// ExceptionExtension copy constructor
		:iFunction(original.iFunction),iLibrary(original.iLibrary),iDetails(original.iDetails)
	{
		// empty body
	} // end ExceptionExtension copy constructor


	virtual ~ExceptionExtension()																	// ExceptionExtension destructor
	{
		// empty body
	} // end ExceptionExtension destructor


	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/

	virtual csr function() const																// function
	{
		return iFunction; 
	} // end function function


	virtual csr library() const																	// library
	{
		return iLibrary; 
	} // end function library


	virtual csr details() const																	// details
	{
		return iDetails;
	} // end function details


private:

	/***************
	* data members *
	***************/

	std::string iFunction;
	std::string iLibrary;
	std::string iDetails;

}; // end class ExceptionExtension


class RuntimeError : public std::runtime_error , public ExceptionExtension
{
public:

	RuntimeError(csr incident , csr library , csr function , csr description)				// RuntimeError constructor
		:runtime_error(incident),ExceptionExtension(library,function,description)
	{
		// empty body
	} // end RuntimeError constructor


	virtual ~RuntimeError()																	// RuntimeError destructor
	{
		// empty body
	} // end RuntimeError destructor

}; // end class RuntimeError


class LogicError : public std::logic_error , public ExceptionExtension
{
public:

	LogicError(csr incident , csr library , csr function , csr description)					// LogicError constructor
		:logic_error(incident),ExceptionExtension(library,function,description)
	{
		// empty body
	} // end LogicError constructor


	virtual ~LogicError()																	// LogicError destructor
	{
		// empty body
	} // end LogicError destructor

}; // end class LogicError


class InvalidArgument : public std::invalid_argument , public ExceptionExtension
{
public:

	InvalidArgument(csr incident , csr library , csr function , csr description)			// InvalidArgument constructor
		:invalid_argument(incident),ExceptionExtension(library,function,description)
	{
		// empty body
	} // end InvalidArgument constructor


	virtual ~InvalidArgument()																// InvalidArgument destructor
	{
		// empty body
	} // end InvalidArgument destructor

}; // end class InvalidArgument


class OutOfRange : public std::out_of_range , public ExceptionExtension
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	OutOfRange(csr incident , csr library , csr function , csr description)		// OutOfRange constructor
		:out_of_range(incident),ExceptionExtension(library,function,description)
	{
		// empty body
	} // end LogicError constructor


	virtual ~OutOfRange()														// OutOfRange destructor
	{
		// empty body
	} // end OutOfRange destructor

}; // end class OutOfRange


class DivideByZeroException : public LogicError
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	DivideByZeroException(csr incident , csr library , csr function , csr description)		// DivideByZeroException constructor
		:LogicError(incident,library,function,description)
	{
		// empty body
	} // end LogicError constructor


	virtual ~DivideByZeroException()														// DivideByZeroException destructor
	{
		// empty body
	} // end DivideByZeroException destructor

}; // end class DivideByZeroException


void ExceptionMessageBox(const std::exception &e , const ExceptionExtension &ee , const char *caption);	// ExceptionMessageBox

#endif // EXCEPTIONS_H
