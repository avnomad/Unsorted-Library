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