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

#ifndef MOUSE_WRAPPER_H
#define MOUSE_WRAPPER_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <windows/common.h>
#include "Device Wrapper.h"


class DIMouse : public DIDevice
{
public:

			/***************************
			* contructors & destructor *
			***************************/

	explicit inline DIMouse(IDirectInput8 *directInputObject)						// DIMouse contructor
		:DIDevice(directInputObject,GUID_SysMouse)
	{
		setDataFormat(&c_dfDIMouse2);
	} // end DIMouse contructor


	inline DIMouse(IDirectInput8 *directInputObject , WindowHandle mainWindow , DWORD mode = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)	// DIMouse contructor
		:DIDevice(directInputObject,GUID_SysMouse)	// DirectInput documentation says the default setting is DISCL_BACKGROUND | DISCL_NONEXCLUSIVE
	{
		setDataFormat(&c_dfDIMouse2);
		setCooperativeLevel(mainWindow,mode);
	} // end DIMouse contructor


	inline ~DIMouse()																// DIMouse destructor
	{
		// just call the base class destructor
	} // end DIMouse destructor



		/************
		* operators *
		************/

		/*******************
		* member functions *
		*******************/


	DIMouse &getState()																// getState
	{
		if(!GetCursorPos(&absolute))
			throw RuntimeError("A GetCursorPosFailure","windows","GetCursorPos","No additional information available");
		// if GetDeviceState does not write in the buffer when it returns
		// DIERR_INPUTLOST then memset should be placed before the loop
		while(memset(&X,0,sizeof(DIMOUSESTATE2)) , !getDeviceState(sizeof(DIMOUSESTATE2),&X))
			acquire();
		return *this;
	} // end function getState


public:

		/***************
		* data members *
		***************/

	POINT absolute;
	LONG X;
	LONG Y;
	LONG Z;
	BYTE button[8];

}; // end class DIMouse

#endif // MOUSE_WRAPPER_H