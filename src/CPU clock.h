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