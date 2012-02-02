#ifndef ENENT_DISPATCHER_H
#define ENENT_DISPATCHER_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif


#include <Direct Input/Keyboard Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>
#include <CPU clock.h>

namespace MouseAndKeyboard
{

class EventDispatcher;	// forward class declaration
struct ButtonHandlerPair
{
	void (*up)(const EventDispatcher & , double);
	void (*down)(const EventDispatcher & , double);
}; // end struct ButtonHandlerPair



class EventDispatcher
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline EventDispatcher(IDirectInput8 *directInputObject)												// EventDispatcher constructor
		:keyboard(directInputObject),mouse(directInputObject),motion(0),wheel(0),
		localKeyboardBufferSize(0),localMouseBufferSize(0),
		localKeyboardBuffer(0),localMouseBuffer(0),iAssumeDigitizer(false)
	{
		memset(button,0,sizeof(button));
		memset(key,0,sizeof(key));
	} // end EventDispatcher constructor


	inline ~EventDispatcher()																				// EventDispatcher destructor
	{
		delete[] localKeyboardBuffer;
		delete[] localMouseBuffer;
	} // end EventDispatcher destructor


	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/

	// a call to this function should be made between a call to
	// mouse::setBufferSize and a call to EventDispatcher::execute.
	inline EventDispatcher &setLocalMouseBuffer()															// setLocalMouseBuffer
	{
		delete[] localMouseBuffer;
		localMouseBufferSize = mouse.getBufferSize();
		localMouseBuffer = new DIDEVICEOBJECTDATA[localMouseBufferSize];
		return *this;
	} // end function setLocalMouseBuffer


	// a call to this function should be made between a call to
	// keyboard::setBufferSize and a call to EventDispatcher::execute.
	inline EventDispatcher &setLocalKeyboardBuffer()														// setLocalKeyboardBuffer
	{
		delete[] localKeyboardBuffer;
		localKeyboardBufferSize = keyboard.getBufferSize();
		localKeyboardBuffer = new DIDEVICEOBJECTDATA[localKeyboardBufferSize];
		return *this;
	} // end function setLocalKeyboardBuffer


	inline EventDispatcher &initializeClock()																// initializeClock
	{
		oldTime = CPUclock::currentTime();
		return *this;
	} // end function initializeClock


	EventDispatcher &execute();																				// execute


	void assumeDigitizer(double initX, double initY, int screenWidth, int screenHeight)						// assumeDigitizer
	{
		iAssumeDigitizer = true;
		iX = initX;
		iY = initY;
		iWidth = screenWidth;
		iHeight = screenHeight;
		xFactor = screenWidth/65535.0;
		yFactor = screenHeight/65535.0;
	} // end function assumeDigitizer


private:
	EventDispatcher &dispatchMouseEvent(const DIDEVICEOBJECTDATA *&mouseBegin , const DIDEVICEOBJECTDATA *mouseEnd , double eventTime);	// dispatchMouseEvent


	inline EventDispatcher &dispatchKeyboardEvent(const DIDEVICEOBJECTDATA &eventData , double eventTime)	// dispatchKeyboardEvent
	{
		if(eventData.dwData & 0x80)	// a key was pressed
		{
			keyboard.key[eventData.dwOfs] = 1;						// update keyboard state and
			if(key[eventData.dwOfs].down)
				key[eventData.dwOfs].down(*this,eventTime);	// call the corresponding handler (if one is present)
		}
		else	// a key was released
		{
			keyboard.key[eventData.dwOfs] = 0;						// update keyboard state and
			if(key[eventData.dwOfs].up)
				key[eventData.dwOfs].up(*this,eventTime);	// call the corresponding handler (if one is present)
		} // end else
		return *this;
	} // end function dispatchKeyboardEvent



	/***************
	* data members *
	***************/

private:
	double oldTime;
	DWORD localKeyboardBufferSize;
	DWORD localMouseBufferSize;
	DIDEVICEOBJECTDATA *localKeyboardBuffer;
	DIDEVICEOBJECTDATA *localMouseBuffer;
	double iX;	// remain uninitialized unless assumeDigitizer is called
	double iY;	// >>
	int iWidth;	// >>
	int iHeight;	// >>
	double xFactor;	// >>
	double yFactor;	// >>
	bool iAssumeDigitizer;	// initialized to false

	// objects of this class should not be copied
	inline EventDispatcher &operator = (const EventDispatcher &){}
public:
	DIKeyboard keyboard;
	DIMouse mouse;

	mutable void (*motion)(const EventDispatcher &,double);
	mutable void (*wheel)(const EventDispatcher &,double);
	mutable ButtonHandlerPair button[8];
	mutable ButtonHandlerPair key[256];
}; // end class EventDispatcher

}; // end namespace MouseAndKeyboard

#endif // ENENT_DISPATCHER_H