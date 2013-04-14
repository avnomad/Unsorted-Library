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

#include "common.h"
#include <iomanip>
using std::setw;

typedef unsigned int ui;

std::ostream &operator<<(std::ostream &outStream , const GUID &guid)
{
	std::ios_base::fmtflags flags = outStream.flags();	// store the old output format.
	char fill = outStream.fill('0');

	outStream << std::right << std::uppercase << std::hex <<	// set the new output format.
		setw(8) << guid.Data1 <<'-'<< setw(4) << guid.Data2 <<'-'<< 
		setw(4) << guid.Data3 <<'-'<< setw(2) << (ui)guid.Data4[0] << setw(2) << (ui)guid.Data4[1] <<'-'<<
		setw(2) << (ui)guid.Data4[2] << setw(2) << (ui)guid.Data4[3] << setw(2) << (ui)guid.Data4[4] <<
		setw(2) << (ui)guid.Data4[5] << setw(2) << (ui)guid.Data4[6] << setw(2) << (ui)guid.Data4[7];

	outStream.fill(fill);	// restore the old output format.
	outStream.flags(flags);
	return outStream;
} // end function operator <<
