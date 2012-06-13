//	Copyright (C) 2009-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

#ifndef DIRECTINPUT_WRAPPER_H
#define DIRECTINPUT_WRAPPER_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <windows/common.h>
#include <exceptions/exceptions.h>

struct DirectInput
{
public:

			/***************************
			* contructors & destructor *
			***************************/

	DirectInput(InstanceHandle applicationInstance)								// DirectInput contructor
	{
		switch(DirectInput8Create(applicationInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&iObject,NULL))
		{
		case DIERR_BETADIRECTINPUTVERSION:
			throw RuntimeError("A BetaDirectInputVersion","DirectInput8","DirectInput8Create","The application was written for an unsupported prerelease version of DirectInput.");
		case DIERR_INVALIDPARAM:
			throw InvalidArgument("An InvalidParameter","DirectInput8","DirectInput8Create","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
		case DIERR_OLDDIRECTINPUTVERSION:
			throw RuntimeError("An OldDirectInputVersion","DirectInput8","DirectInput8Create","The application requires a newer version of DirectInput.");
		case DIERR_OUTOFMEMORY:
			throw RuntimeError("An OutOfMemory","DirectInput8","DirectInput8Create","The DirectInput subsystem could not allocate sufficient memory to complete the call.");
		default:
			throw RuntimeError("An UnknownError","DirectInput8","DirectInput8Create","The above function returned an unexpected error code. This shouldn't normally happen.");
		case DI_OK:	// everything in order
			break;
		} // end switch
	} // end DirectInput contructor


	inline ~DirectInput()														// DirectInput destructor
	{
		iObject->Release();
	} // end DirectInput destructor



			/************
			* operators *
			************/

	inline bool operator == (const DirectInput &right) const					// operator ==
	{
		return iObject == right.iObject;
	} // end function operator ==


	inline bool operator != (const DirectInput &right) const					// operator !=
	{
		return iObject != right.iObject;
	} // end function operator !=


	inline operator IDirectInput8 *() const										// operator IDirectInput8 *
	{
		return iObject;
	} // end function operator IDirectInput8 *


			/*******************
			* member functions *
			*******************/

	DirectInput &enumerateDevices(DWORD filter,LPDIENUMDEVICESCALLBACK f,LPVOID data,DWORD flags)	// enumerateDevices
	{
		switch(iObject->EnumDevices(filter,f,data,flags))
		{
		case DIERR_INVALIDPARAM:
			throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::EnumObjects","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
		case DIERR_NOTINITIALIZED:
			throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::EnumObjects","This object has not been initialized.");
		default:
#ifdef DEBUG
			throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::EnumObjects","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
		case DI_OK:	// everything in order
			return *this;
		} // end switch
	} // end function enumerateDevices


private:

		/***************
		* data members *
		***************/

	IDirectInput8 *iObject;

	inline DirectInput(const DirectInput &original){}	// passing objects of this class by value is prohibited.
}; // end class DirectInput

#endif // DIRECTINPUT_WRAPPER_H
