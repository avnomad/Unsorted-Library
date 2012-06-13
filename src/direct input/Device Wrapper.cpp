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

#include "Device Wrapper.h"

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif


DIPROPDWORD DIDevice::value = {{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},0};


DIDevice::DIDevice(IDirectInput8 *directInputObject , const GUID &deviceID)												// DIDevice contructor
{
	// create the keyboard device
	switch(directInputObject->CreateDevice(deviceID,&iObject,NULL))
	{
	case DIERR_DEVICENOTREG:
		throw LogicError("A DeviceNotRegistered","DirectInput8","IDirectInput8::CreateDevice","The device or device instance is not registered with DirectInput. This may be due to an incorrect GUID");
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInput8::CreateDevice","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOINTERFACE:
		throw LogicError("A NoInterface","DirectInput8","IDirectInput8::CreateDevice","The object does not support the specified interface.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInput8::CreateDevice","This object has not been initialized.");
	case DIERR_OUTOFMEMORY:
		throw RuntimeError("An OutOfMemory","DirectInput8","IDirectInput8::CreateDevice","The DirectInput subsystem could not allocate sufficient memory to complete the call.");
	default:
#ifdef DEBUG		
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInput8::CreateDevice","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_OK:	// everything in order
		break;
	} // end switch
} // end DIDevice contructor


DIDevice &DIDevice::setDataFormat(const DIDATAFORMAT *dataFormat)														// setDataFormat
{
	switch(iObject->SetDataFormat(dataFormat))
	{
	case DIERR_ACQUIRED:
		throw LogicError("A DeviceAcquired","DirectInput8","IDirectInputDevice8::SetDataFormat","The operation cannot be performed while the device is acquired.");
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::SetDataFormat","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::SetDataFormat","This object has not been initialized.");
	default:
#ifdef DEBUG		
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::SetDataFormat","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_OK:	// everything in order
		return *this;
	} // end switch
} // end function setDataFormat


DIDevice &DIDevice::setCooperativeLevel(WindowHandle mainWindow , DWORD mode)											// setCooperativeLevel
{
	switch(iObject->SetCooperativeLevel(mainWindow,mode))
	{
	case E_HANDLE:
		throw LogicError("An InvalidWindowHandle","DirectInput8","IDirectInputDevice8::SetCooperativeLevel","The window handle parameter is not a valid top-level window that belongs to the process.");
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::SetCooperativeLevel","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::SetCooperativeLevel","This object has not been initialized.");
	default:
#ifdef DEBUG
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::SetCooperativeLevel","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_OK:	// everything in order
		return *this;
	} // end switch
} // end function setCooperativeLevel


DIDevice &DIDevice::acquire()																							// acquire
{
	switch(iObject->Acquire())
	{
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::Acquire","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::Acquire","This object has not been initialized.");
	case DIERR_OTHERAPPHASPRIO:
		//throw RuntimeError("An OtherApplicationHasPriority","DirectInput8","IDirectInputDevice8::Acquire","Another application has a higher priority level, preventing this call from succeeding. This error can occur when an application has only foreground access to a device but is attempting to acquire the device while in the background.");
		return *this;
	default:
#ifdef DEBUG		
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::Acquire","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case S_FALSE:	// succeded, but the device was already acquired so this call was redundant.
#ifdef DEBUG
		throw LogicError("An AlreadyAcquired","DirectInput8","IDirectInputDevice8::Acquire","The device was already acquired and thus this call was redundant.");
#endif
	case DI_OK:	// everything in order
		return *this;
	} // end switch
} // end function acquire


bool DIDevice::getDeviceState(DWORD bufferSize , VOID *stateBuffer)														// getDeviceState
{
	switch(iObject->GetDeviceState(bufferSize,stateBuffer))
	{
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::GetDeviceState","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::GetDeviceState","This object has not been initialized.");
	case E_PENDING:
		throw RuntimeError("A DataPending","DirectInput8","IDirectInputDevice8::GetDeviceState","Data is not yet available.");
	case DIERR_NOTACQUIRED:
		throw LogicError("A NotAcquired","DirectInput8","IDirectInputDevice8::GetDeviceState","The operation cannot be performed unless the device is acquired.");
		/*	From MSDN:
			"You should not attempt to reacquire the mouse on getting a DIERR_NOTACQUIRED error. 
			If you do, you could get caught in an infinite loop - acquisition would again fail, 
			you would get another DIERR_NOTACQUIRED error, and so on."

			On the other hand it seems to return DIERR_NOTACQUIRED in cases it shouldn't and 
			work after a while if you try to reacquire it...

			Documentation sais in some cases if function returns DIERR_NOTACQUIRED the problem
			can be solved by unacquiring and acquiring the device again manually.
		*/
		//return false;
	case DIERR_INPUTLOST:	// Access to the input device has been lost. It must be reacquired.
		return false;
	default:
#ifdef DEBUG
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::GetDeviceState","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_OK:	// everything in order
		return true;
	} // end switch
} // end function getDeviceState


DIDevice &DIDevice::enumObjects(LPDIENUMDEVICEOBJECTSCALLBACK f , VOID *data , DWORD subset)							// enumObjects
{
	switch(iObject->EnumObjects(f,data,subset))
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
} // end function enumObjects


bool DIDevice::getDeviceData(DWORD elementSize , DIDEVICEOBJECTDATA *destination , DWORD *elementsCount , DWORD mode)	// getDeviceData
{
	switch(iObject->GetDeviceData(elementSize,destination,elementsCount,mode))
	{
	case DI_BUFFEROVERFLOW:
		throw RuntimeError("A BufferOverflow","DirectInput8","IDirectInputDevice8::GetDeviceData","The device buffer overflowed and some input was lost.");
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::GetDeviceData","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::GetDeviceData","This object has not been initialized.");
	case DIERR_NOTBUFFERED:
		throw LogicError("A NotBuffered","DirectInput8","IDirectInputDevice8::GetDeviceData","The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering.");
	case DIERR_NOTACQUIRED:
		throw LogicError("A NotAcquired","DirectInput8","IDirectInputDevice8::GetDeviceData","The operation cannot be performed unless the device is acquired.");
	case DIERR_INPUTLOST:	// Access to the input device has been lost. It must be reacquired.
		return false;
	default:
#ifdef DEBUG
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::GetDeviceData","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_OK:	// everything in order
		return true;
	} // end switch
} // end function getDeviceData


DIDevice &DIDevice::getProperty(const GUID &propertyID , DIPROPHEADER *value)											// getProperty
{
	switch(iObject->GetProperty(propertyID,value))
	{
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::GetProperty","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::GetProperty","This object has not been initialized.");
	case DIERR_NOTEXCLUSIVEACQUIRED:
		throw LogicError("A NotExclusivelyAcquired","DirectInput8","IDirectInputDevice8::GetProperty","The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.");
	case DIERR_OBJECTNOTFOUND:
		throw LogicError("An ObjectNotFound","DirectInput8","IDirectInputDevice8::GetProperty","The requested object does not exist.");
	case DIERR_UNSUPPORTED:
		throw RuntimeError("An UnsupportedFunction","DirectInput8","IDirectInputDevice8::GetProperty","The function called is not supported at this time.");
	default:
#ifdef DEBUG
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::GetProperty","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case S_FALSE:
#ifdef DEBUG
		throw LogicError("A NoEffect","DirectInput8","IDirectInputDevice8::GetProperty","The above function had no effect.");
#endif
	case DI_OK:	// everything in order
		return *this;
	} // end switch
} // end function getProperty


DIDevice &DIDevice::setProperty(const GUID &propertyID , const DIPROPHEADER *value)										// setProperty
{
	switch(iObject->SetProperty(propertyID,value))
	{
	case DIERR_INVALIDPARAM:
		throw InvalidArgument("An InvalidParameter","DirectInput8","IDirectInputDevice8::SetProperty","An invalid parameter was passed to the above function, or the object was not in a state that permitted the function to be called.");
	case DIERR_NOTINITIALIZED:
		throw LogicError("A NotInitialized","DirectInput8","IDirectInputDevice8::SetProperty","This object has not been initialized.");
	case DIERR_OBJECTNOTFOUND:
		throw LogicError("An ObjectNotFound","DirectInput8","IDirectInputDevice8::SetProperty","The requested object does not exist.");
	case DIERR_UNSUPPORTED:
		throw RuntimeError("An UnsupportedFunction","DirectInput8","IDirectInputDevice8::SetProperty","The function called is not supported at this time.");
	default:
#ifdef DEBUG
		throw RuntimeError("An UnknownError","DirectInput8","IDirectInputDevice8::SetProperty","The above function returned an unexpected error code. This shouldn't normally happen.");
#endif
	case DI_PROPNOEFFECT:
#ifdef DEBUG
		throw LogicError("A NoEffect","DirectInput8","IDirectInputDevice8::SetProperty","The change in device properties had no effect.");
#endif
	case DI_OK:	// everything in order
		return *this;
	} // end switch
} // end function setProperty
