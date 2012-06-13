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

#ifndef KEYBOARD_WRAPPER_H
#define KEYBOARD_WRAPPER_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <windows/common.h>
#include "Device Wrapper.h"


class DIKeyboard : public DIDevice
{
public:

			/***************************
			* contructors & destructor *
			***************************/

	explicit inline DIKeyboard(IDirectInput8 *directInputObject)						// DIKeyboard contructor
		:DIDevice(directInputObject,GUID_SysKeyboard)
	{
		setDataFormat(&c_dfDIKeyboard);
	} // end DIKeyboard contructor


	inline DIKeyboard(IDirectInput8 *directInputObject , WindowHandle mainWindow , DWORD mode = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)	// DIKeyboard contructor
		:DIDevice(directInputObject,GUID_SysKeyboard)
	{
		setDataFormat(&c_dfDIKeyboard);
		setCooperativeLevel(mainWindow,mode);
	} // end DIKeyboard contructor


	inline ~DIKeyboard()																// DIKeyboard destructor
	{
		// just call the base class destructor
	} // end DIKeyboard destructor



		/************
		* operators *
		************/

		/*******************
		* member functions *
		*******************/

	DIKeyboard &getState()																// getState
	{
		// if GetDeviceState does not write in the buffer when it returns
		// DIERR_INPUTLOST then memset should be placed before the loop
		while(memset(key,0,sizeof(key)) , !getDeviceState(sizeof(key),key))
			acquire();
		return *this;
	} // end function getState


public:

		/***************
		* data members *
		***************/

	BYTE key[256];

}; // end class DIKeyboard

#endif // KEYBOARD_WRAPPER_H