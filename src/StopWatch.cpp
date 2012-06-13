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

#include "StopWatch.h"


				/**************
				* contructors *
				**************/

	StopWatch::StopWatch(const std::string &timeUnit)					// default constructor
		:iUnit(timeUnit)
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		if(!timeUnit.compare("ms"))		// fragments of second
			iMultiplier = 1e3;
		else if(!timeUnit.compare("ìs"))
			iMultiplier = 1e6;
		else if(!timeUnit.compare("ns"))
			iMultiplier = 1e9;
		else if(!timeUnit.compare("ps"))
			iMultiplier = 1e12;
		else if(!timeUnit.compare("ks"))	// multiples of second
			iMultiplier = 1e-3;
		else if(!timeUnit.compare("Ms"))
			iMultiplier = 1e-6;
		else if(!timeUnit.compare("Gs"))
			iMultiplier = 1e-9;
		else if(!timeUnit.compare("Ts"))
			iMultiplier = 1e-12;
		else						// seconds
			iMultiplier = 1.0;

		iMultiplier /= frequency.QuadPart;
	} // end StopWatch default constructor




				/*******************
				* global operators *
				*******************/

std::ostream &operator<<(std::ostream &outStream, StopWatch &timer)				 // operator <<
{
	outStream << std::setw(15) << timer.pop() << timer.getUnit() << " passed since last checkpoint." << std::endl;
	return outStream;
} // end function operator <<
