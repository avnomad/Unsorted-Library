#ifndef CPU_CLOCK_H
#define CPU_CLOCK_H

// includes
#include <string>
#include <windows.h>

class CPUclock
{
public:

			/*******************
			* member functions *
			*******************/

	static inline double currentTime()														// currentTime
	{
		LARGE_INTEGER ticks;					// 64 bit integer
		//DWORD oldMask = SetThreadAffinityMask(GetCurrentThread(),1);	// allways get the time from logical processor 0
		QueryPerformanceCounter(&ticks);		// get CPU clock ticks since... you switched on your PC?
		//SetThreadAffinityMask(GetCurrentThread(),oldMask);	// time may vary between processors due to bugs...

		return ticks.QuadPart*unit.multiplier;	// convert them to the selected time unit and return them.
	} // end function currentTime


	static void setUnit(const std::string &timeUnit);										// setUnit
								// does not change the values noted so far.

	static inline const std::string &getUnit()												// getUnit
	{
		return unit.name;
	} // end function getUnit



private:

			/***************
			* data members *
			***************/

#include <CPU clock/Unit.h>
	static Unit unit;
}; // end class CPUclock

#endif // CPU_CLOCK_H