#ifndef DEVICE_WRAPPER_H
#define DEVICE_WRAPPER_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <windows/common.h>
#include <exceptions/exceptions.h>


class DIDevice
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	DIDevice(IDirectInput8 *directInputObject , const GUID &deviceID);					// DIDevice contructor


	inline DIDevice(IDirectInputDevice8 *object)										// DIDevice conversion constructor
		:iObject(object)
	{
		// empty body
	} // end DIDevice conversion constructor


	inline ~DIDevice()																	// DIDevice destructor
	{
		unacquire().iObject->Release();
	} // end DIDevice destructor



	/************
	* operators *
	************/

	inline bool operator == (const DIDevice &right) const								// operator ==
	{
		return iObject == right.iObject;
	} // end function operator ==


	inline bool operator != (const DIDevice &right) const								// operator !=
	{
		return iObject != right.iObject;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	DIDevice &setDataFormat(const DIDATAFORMAT *dataFormat);														// setDataFormat
	DIDevice &setCooperativeLevel(WindowHandle mainWindow , DWORD mode);											// setCooperativeLevel
	DIDevice &enumObjects(LPDIENUMDEVICEOBJECTSCALLBACK f , VOID *data , DWORD subset);								// enumObjects
	DIDevice &acquire();																							// acquire
	bool getDeviceState(DWORD bufferSize , VOID *stateBuffer);	// true for success									// getDeviceState
	bool getDeviceData(DWORD elementSize , DIDEVICEOBJECTDATA *destination , DWORD *elementsCount , DWORD mode);	// getDeviceData
	DIDevice &getProperty(const GUID &propertyID , DIPROPHEADER *value);											// getProperty
	DIDevice &setProperty(const GUID &propertyID , const DIPROPHEADER *value);										// setProperty


	inline DIDevice &unacquire()														// unacquire
	{
		switch(iObject->Unacquire())
		{
		default:
#ifdef DEBUG
			throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::Unacquire","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
		case DI_NOEFFECT:
		case DI_OK:	// everything in order
			return *this;
		} // end switch
	} // end function unacquire


	inline DWORD getBufferSize()														// getBufferSize
	{
		getProperty(DIPROP_BUFFERSIZE,&value.diph);
		return value.dwData;
	} // end function getBufferSize


	inline DIDevice &setBufferSize(DWORD size)											// setBufferSize
	{
		value.dwData = size;
		setProperty(DIPROP_BUFFERSIZE,&value.diph);
		return *this;
	} // end function setBufferSize


private:

	/***************
	* data members *
	***************/

	IDirectInputDevice8 *iObject;

	inline DIDevice(const DIDevice &){}	// objects of this class should not be copied
	inline DIDevice &operator = (const DIDevice &){}

	static DIPROPDWORD value;
}; // end class DIDevice

#endif // DEVICE_WRAPPER_H
