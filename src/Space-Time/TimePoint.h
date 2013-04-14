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

#ifndef TIMEPOINT_H
#define TIMEPOINT_H

// #includes:
#include <string>
#include <windows.h>

// #defines
#define NOW Dummy(Dummy(0))

struct Dummy{inline Dummy(int){}};	// a dummy class declaration to disambiguate
				// the call some constructors


template<typename FloatingPointType = double>	// the class may not work properly if FloatingPointType is not a floating point type.
class TimePoint
{		
public:
	
	/***************************
	* contructors & destructor *
	***************************/

	inline TimePoint()																// TimePoint default constructor
	{
		// do nothing
	} // end TimePoint default constructor


	inline TimePoint(const TimePoint &original)										// TimePoint copy constructor
		:t(original.t)
	{
		// empty body
	} // end TimePoint copy constructor


	inline TimePoint(FloatingPointType T)											// TimePoint conversion constructor
		:t(T)
	{
		// empty body
	} // end TimePoint conversion constructor


	inline TimePoint(Dummy)															// TimePoint constructor
	{							// initialize with current time.
		setT();
	} // end TimePoint constructor


	inline ~TimePoint()																// TimePoint destructor
	{
		// empty body
	} // end TimePoint destructor




	/************
	* operators *
	************/

	inline TimePoint &operator = (const TimePoint &original)						// operator =
	{
		t = original.t;
		return *this;
	} // end function operator =


	inline bool operator == (const TimePoint &right) const							// operator ==
	{
		return t == right.t;
	} // end function operator ==


	inline bool operator != (const TimePoint &right) const							// operator !=
	{
		return t != right.t;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline TimePoint &setT(FloatingPointType T)												// setT
	{
		t = T;
		return *this;
	} // end function setT


	inline TimePoint &setT()																// setT
	{							// initialize with current time.
		LARGE_INTEGER ticks;					// 64 bit integer
		QueryPerformanceCounter(&ticks);		// get CPU clock ticks since... you switched on your PC?

		t =  ticks.QuadPart*unit.multiplier;	// convert them to the used time unit and store them.
		return *this;
	} // end function setT


	static void setUnit(const std::string &timeUnit)										// setUnit
	{									// does not change the values noted so far.
		LARGE_INTEGER clockFrequency;
		QueryPerformanceFrequency(&clockFrequency);

		if(!timeUnit.compare("ms"))			// fragments of second
			unit.multiplier = 1e3;
		else if(!timeUnit.compare("ìs"))
			unit.multiplier = 1e6;
		else if(!timeUnit.compare("ns"))
			unit.multiplier = 1e9;
		else if(!timeUnit.compare("ps"))
			unit.multiplier = 1e12;
		else if(!timeUnit.compare("ks"))	// multiples of second
			unit.multiplier = 1e-3;
		else if(!timeUnit.compare("Ms"))
			unit.multiplier = 1e-6;
		else if(!timeUnit.compare("Gs"))
			unit.multiplier = 1e-9;
		else if(!timeUnit.compare("Ts"))
			unit.multiplier = 1e-12;
		else								// seconds
			unit.multiplier = 1.0;

		unit.multiplier /= clockFrequency.QuadPart;
		unit.name = timeUnit;
	} // end function setUnit


	static inline const std::string &getUnit()												// getUnit
	{
		return unit.name;
	} // end function getUnit


	/***************
	* data members *
	***************/

	FloatingPointType t;

private:

#include "TimePoint/Unit.h"
	static Unit unit;
}; // end class TimePoint

template<typename FloatingPointType>
typename TimePoint<FloatingPointType>::Unit TimePoint<FloatingPointType>::unit;

#endif // TIMEPOINT_H