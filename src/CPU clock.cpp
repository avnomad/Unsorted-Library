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

#include "CPU clock.h"

CPUclock::Unit CPUclock::unit;


void CPUclock::setUnit(const std::string &timeUnit)										// setUnit
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
