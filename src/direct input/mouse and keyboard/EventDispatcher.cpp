#include "EventDispatcher.h"
#include <algorithm>
using std::count_if;

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;
#include <iomanip>
using std::setw;
using std::setprecision;

ofstream sequence("sequence.txt");
#endif



namespace MouseAndKeyboard
{

struct NotSame
{
	NotSame(){}																							// constructor
	NotSame(DWORD sequence):oldSequence(sequence){}														// constructor

	bool operator ()(const DIDEVICEOBJECTDATA &eventData)												// operator ()
	{
		if(DISEQUENCE_COMPARE(eventData.dwSequence,!=,oldSequence))
		{
			oldSequence = eventData.dwSequence;
			return true;
		}
		else
			return false;
	} // end function operator ()

	DWORD oldSequence;
}; // end struct NotSame



EventDispatcher &EventDispatcher::execute()														// execute
{
#ifdef DEBUG
	if(!sequence) throw RuntimeError("A CouldNotOpenFile","std","ofstream::ofstream","No additional information.");
	sequence<<std::fixed<<setprecision(0);
	int e1 = -1;
	int e2 = -1;
#endif
	int n1 = -1;	// may be deleted later.
	int n2 = -1;
	bool mouseLost = false;
	bool keyboardLost = false;
	double timePeriod;
	double mouseEventPeriod;
	double keyboardEventPeriod;
	double mouseEventTime;
	double keyboardEventTime;
	NotSame mouseNotSame;
	NotSame keyboardNotSame;
	union
	{
		DWORD keyboardEvents;
		const DIDEVICEOBJECTDATA *keyboardEnd;
	};	// keyboardEvents and keyboardEnd will occupy the same memory.
	union
	{
		DWORD mouseEvents;
		const DIDEVICEOBJECTDATA *mouseEnd;
	};	// mouseEvents and mouseEnd will occupy the same memory.
	const DIDEVICEOBJECTDATA *keyboardBegin = localKeyboardBuffer;	// set keyboardBegin to point to the beginning of localKeyboardBuffer.
	const DIDEVICEOBJECTDATA *mouseBegin = localMouseBuffer;	// set mouseBegin to point to the beginning of localMouseBuffer.

	keyboardEvents = localKeyboardBufferSize;	// initialize keyboardEvents with the localKeyboardBufferSize (the whole buffer will be read).
	mouseEvents = localMouseBufferSize;	// initialize mouseEvents with the localMouseBufferSize (the whole buffer will be read).
	keyboardLost = !keyboard.getDeviceData(sizeof(DIDEVICEOBJECTDATA),localKeyboardBuffer,&keyboardEvents,0);	// read the keyboard buffer.
																	// keyboardEvents will be holding the number of events read from the buffer.
	timePeriod = CPUclock::currentTime() - oldTime;	// note how much time passed between the previous call to mouse::getDeviceData
	mouseEventTime = keyboardEventTime = oldTime;	// both the first mouse and keyboard events are assumed to have occured the last time we checked the time.
	oldTime += timePeriod;							// and this call to mouse::getDeviceData. Then update the oldTime.
	mouseLost = !mouse.getDeviceData(sizeof(DIDEVICEOBJECTDATA),localMouseBuffer,&mouseEvents,0);	// read the keyboard buffer. mouseEvents
																					// will be holding the number of events read from the buffer.
#ifdef DEBUG
	e1 = mouseEvents;
	e2 = keyboardEvents;
#endif
	keyboardEnd = localKeyboardBuffer+keyboardEvents;	// set keyboardEnd to point to the end of localKeyboardBuffer. keyboardEvents should not
														// be used again after that. (occupies the same memory as keyboardEnd)
	mouseEnd = localMouseBuffer+mouseEvents;	// set mouseEnd to point to the end of localMouseBuffer. mouseEvents should not
												// be used again after that. (occupies the same memory as mouseEnd)
	if(mouseBegin != mouseEnd)	// avoid division by zero.
	{
		n1 = count_if(mouseBegin,mouseEnd,NotSame(0));
		mouseEventPeriod = timePeriod / n1;	// set mouseEventPeriod to the average time between 2 mouse events.
		mouseNotSame.oldSequence = mouseBegin->dwSequence;
	} // end if
	if(keyboardBegin != keyboardEnd) // avoid divition by zero.
	{
		n2 = count_if(keyboardBegin,keyboardEnd,NotSame(0));
		keyboardEventPeriod = timePeriod / n2;	// set keyboardEventPeriod to the average time between 2 keyboard events.
		keyboardNotSame.oldSequence = keyboardBegin->dwSequence;
	} // end if

#ifdef DEBUG
	double dummy = 0.0;
#endif

	while(mouseBegin != mouseEnd && keyboardBegin != keyboardEnd)
		if(DISEQUENCE_COMPARE(mouseBegin->dwSequence,<,keyboardBegin->dwSequence))
		{
			if(mouseNotSame(*mouseBegin))
				mouseEventTime += mouseEventPeriod;
#ifdef DEBUG
			if(mouseEventTime < 100 || mouseEventTime==1/dummy || mouseEventTime==-1/dummy)
				throw std::exception();
#endif
			dispatchMouseEvent(mouseBegin,mouseEnd,mouseEventTime);
#ifdef DEBUG
			sequence<<'m'<<setw(15)<<mouseBegin->dwSequence<<setw(5)<<mouseBegin->dwOfs<<
				setw(15)<<mouseBegin->dwTimeStamp<<setw(15)<<mouseEventTime<<'\n';
#endif
			++mouseBegin;
		}
		else
		{
			if(keyboardNotSame(*keyboardBegin))
				keyboardEventTime += keyboardEventPeriod;
#ifdef DEBUG
			if(keyboardEventTime < 100 || keyboardEventTime==1/dummy || keyboardEventTime==-1/dummy)
				throw std::exception();
#endif
			dispatchKeyboardEvent(*keyboardBegin,keyboardEventTime);
#ifdef DEBUG
			sequence<<'k'<<setw(15)<<keyboardBegin->dwSequence<<setw(5)<<keyboardBegin->dwOfs<<
				setw(15)<<keyboardBegin->dwTimeStamp<<setw(15)<<keyboardEventTime<<'\n';
#endif
			++keyboardBegin;
		} // end else

	if(mouseBegin == mouseEnd)	// the mouse events ran out first
		while(keyboardBegin != keyboardEnd)
		{
			if(keyboardNotSame(*keyboardBegin))
				keyboardEventTime += keyboardEventPeriod;
#ifdef DEBUG
			if(keyboardEventTime < 100 || keyboardEventTime==1/dummy || keyboardEventTime==-1/dummy)
				throw std::exception();
#endif
			dispatchKeyboardEvent(*keyboardBegin,keyboardEventTime);
#ifdef DEBUG
			sequence<<'k'<<setw(15)<<keyboardBegin->dwSequence<<setw(5)<<keyboardBegin->dwOfs<<
				setw(15)<<keyboardBegin->dwTimeStamp<<setw(15)<<keyboardEventTime<<'\n';
#endif
			++keyboardBegin;
		} // end while
	else
		while(mouseBegin != mouseEnd)
		{
			if(mouseNotSame(*mouseBegin))
				mouseEventTime += mouseEventPeriod;
#ifdef DEBUG
			if(mouseEventTime < 100 || mouseEventTime==1/dummy || mouseEventTime==-1/dummy)
				throw std::exception();
#endif
			dispatchMouseEvent(mouseBegin,mouseEnd,mouseEventTime);
#ifdef DEBUG
			sequence<<'m'<<setw(15)<<mouseBegin->dwSequence<<setw(5)<<mouseBegin->dwOfs<<
				setw(15)<<mouseBegin->dwTimeStamp<<setw(15)<<mouseEventTime<<'\n';
#endif
			++mouseBegin;
		} // end while
#ifdef DEBUG
	sequence<<endl;
#endif
	if(mouseLost)
	{
		exit(0);
		// just ignore it for now...
	} // end if
	if(keyboardLost)
	{
		exit(0);
		// just ignore it for now...

	//	BYTE newKey[256];

	//	do{
	//		keyboard.acquire();	// clear newKey and store the current keyboard state in it.
	//	}while(memset(newKey,0,sizeof(newKey)) , !keyboard.getDeviceState(sizeof(newKey),newKey));

	//	for(int c = 0 ; c < 256 ; ++c)	// for each key in the keyboard
	//		if((newKey[c] & 0x80) && !keyboard.key[c])	// if a key was pressed
	//		{
	//			keyboard.key[c] = 1;	// update keyboard state and
	//			if(key[c].down)	// (if one is present)
	//				key[c].down(*this,oldTime);	// call the corresponding handler
	//		}																					// any better ideas about the time?
	//		else if(!(newKey[c] & 0x80) && keyboard.key[c])	// else if a key was released
	//		{
	//			keyboard.key[c] = 0;	// update keyboard state and
	//			if(key[c].up)	// (if one is present)
	//				key[c].up(*this,oldTime);	// call the corresponding handler
	//		} // end else
	} // end if


	return *this;											// the best thing would be to count the stanges in state  too (in cast of INPUTLOST)
															// to determine a more accurate event count and a better eventPeriod.
} // end function execute

#define TABLET

EventDispatcher &EventDispatcher::dispatchMouseEvent(const DIDEVICEOBJECTDATA *&mouseBegin , const DIDEVICEOBJECTDATA *mouseEnd , double eventTime)	// dispatchMouseEvent
{
#ifdef TABLET
	static double X = 512;
	static double Y = 384;
#endif
	DWORD xOffset = 0;
	DWORD yOffset = (DWORD)&mouse.Y - (DWORD)&mouse.X;	// should be sizeof(LONG)
	DWORD wheelOffset = (DWORD)&mouse.Z - (DWORD)&mouse.X;	// should be 2*sizeof(LONG)
	DWORD buttonOffset = (DWORD)&mouse.button[0] - (DWORD)&mouse.X;	// should be 3*sizeof(LONG)

	if(mouseBegin->dwOfs == xOffset)	// if there was a move on the x axis
	{
		mouse.X = mouseBegin->dwData;	// update X.
		if(mouseBegin+1 != mouseEnd &&	// if there is another event.
			DISEQUENCE_COMPARE(mouseBegin->dwSequence,==,(mouseBegin+1)->dwSequence) &&	// and that event happened simultaneously
			(mouseBegin+1)->dwOfs == yOffset)	// and it is a move on the y axis
		{
			++mouseBegin;	// consume the other event too.
			mouse.Y = mouseBegin->dwData;	// update Y.
		}
		else
		{
			mouse.Y = 0;
		} // end else
		//GetCursorPos(&mouse.absolute);	// update the absolute position (DirectInput reports the relative motion)
#ifndef TABLET
		mouse.absolute.x += mouse.X;
		mouse.absolute.y += mouse.Y;
#else
		X += mouse.X/64.0;
		Y += mouse.Y/85.3333;
		mouse.absolute.x = X;
		mouse.absolute.y = Y;
#endif
		if(motion) motion(*this,eventTime);	// call the motion handler (if one it's present)
	}
	else if(mouseBegin->dwOfs == yOffset)	// if there was a move on the y axis
	{
		mouse.Y = mouseBegin->dwData;	// update Y.
		if(mouseBegin+1 != mouseEnd &&	// if there is another event.
			DISEQUENCE_COMPARE(mouseBegin->dwSequence,==,(mouseBegin+1)->dwSequence) &&	// and that event happened simultaneously
			(mouseBegin+1)->dwOfs == xOffset)	// and it is a move on the x axis
		{
			++mouseBegin;	// consume the other event too.
			mouse.X = mouseBegin->dwData;	// update X.
		}
		else
		{
			mouse.X = 0;
		} // end else
		//GetCursorPos(&mouse.absolute);	// update the absolute position (DirectInput reports the relative motion)
#ifndef TABLET
		mouse.absolute.x += mouse.X;
		mouse.absolute.y += mouse.Y;
#else
		X += mouse.X/64.0;
		Y += mouse.Y/85.3333;
		mouse.absolute.x = X;
		mouse.absolute.y = Y;
#endif
		if(motion) motion(*this,eventTime);	// call the motion handler (if one it's present)
	}
	else if(mouseBegin->dwOfs == wheelOffset)	// if there was a move on the z axis (the wheel)
	{
		mouse.Z = mouseBegin->dwData;	// update Z (wheel)
		if(wheel) wheel(*this,eventTime);	// call the wheel handler (if one it's present)
	}
	else	// a button was pressed or released
	{
		DWORD n = mouseBegin->dwOfs - buttonOffset;	// calculate the offset in the buttons array.
		if(mouseBegin->dwData & 0x80)	// a button was pressed
		{
			mouse.button[n] = 1;	// update the state of the corresponding button and
			if(button[n].down)	// (if it is present)
				button[n].down(*this,eventTime);	// call the corresponding handler
		}
		else	// a button was released
		{
			mouse.button[n] = 0;	// update the state of the corresponding button and
			if(button[n].up)	// (if it is present)
				button[n].up(*this,eventTime);	// call the corresponding handler
		} // end else
	} // end else
	return *this;
} // end function dispatchMouseEvent

}; // end namespace MouseAndKeyboard
