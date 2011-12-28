#ifndef WINDOWS_EXCEPTIONS_H
#define WINDOWS_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

class WindowsLibraryException
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	WindowsLibraryException(const std::string &library , const std::string &function , const std::string &description)	// WindowsLibraryException constructor
		:iFunction(function),iLibrary(library),iDetails(description)
	{
		// empty body
	} // end WindowsLibraryException constructor


	WindowsLibraryException(const WindowsLibraryException &original)													// WindowsLibraryException copy constructor
		:iFunction(original.iFunction),iLibrary(original.iLibrary),iDetails(original.iDetails)
	{
		// empty body
	} // end WindowsLibraryException copy constructor


	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/

	virtual const std::string &function() const											// function
	{
		return iFunction; 
	} // end function function


	virtual const std::string &library() const											// library
	{
		return iLibrary; 
	} // end function library


	virtual const std::string &details() const											// details
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

}; // end class WindowsLibraryException


class WindowsLibraryRuntimeError : public std::runtime_error , public WindowsLibraryException
{
public:

	WindowsLibraryRuntimeError(const std::string &incident , const std::string &library , const std::string &function , const std::string &description)	// WindowsLibraryRuntimeError constructor
		:runtime_error(incident),WindowsLibraryException(library,function,description)
	{
		// empty body
	} // end WindowsLibraryRuntimeError constructor

}; // end class WindowsLibraryRuntimeError


class WindowsLibraryLogicError : public std::logic_error , public WindowsLibraryException
{
public:

	WindowsLibraryLogicError(const std::string &incident , const std::string &library , const std::string &function , const std::string &description)	// WindowsLibraryLogicError constructor
		:logic_error(incident),WindowsLibraryException(library,function,description)
	{
		// empty body
	} // end WindowsLibraryLogicError constructor

}; // end class WindowsLibraryLogicError


class WindowsLibraryInvalidArgument : public std::invalid_argument , public WindowsLibraryException
{
public:

	WindowsLibraryInvalidArgument(const std::string &incident , const std::string &library , const std::string &function , const std::string &description)	// WindowsLibraryInvalidArgument constructor
		:invalid_argument(incident),WindowsLibraryException(library,function,description)
	{
		// empty body
	} // end WindowsLibraryInvalidArgument constructor

}; // end class WindowsLibraryInvalidArgument


void ExceptionMessageBox(const std::exception &e , const WindowsLibraryException &we , const char *caption)
{
	MessageBox(0,(e.what()+we.library()+" function "+we.function()+".\n\n"+we.details()).c_str(),caption,MB_ICONERROR);
} // end function ExceptionMessageBox

#endif // WINDOWS_EXCEPTIONS_H
