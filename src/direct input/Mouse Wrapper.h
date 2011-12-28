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
		:DIDevice(directInputObject,GUID_SysMouse)
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