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

inline bool inRange(signed char x)								// inRange (signed char)
{
	return true;
} // end function inRange


inline bool inRange(short x)									// inRange (short)
{
	return true;
} // end function inRange


inline bool inRange(int x)										// inRange (int)
{
	return true;
} // end function inRange


inline bool inRange(float x)									// inRange (float)
{
	return 0.0 <= x && x <= 1.0;
} // end function inRange


inline bool inRange(double x)									// inRange (double)
{
	return 0.0 <= x && x <= 1.0;
} // end function inRange


inline bool inRange(unsigned char x)							// inRange (unsigned char)
{
	return true;
} // end function inRange


inline bool inRange(unsigned short x)							// inRange (unsigned short)
{
	return true;
} // end function inRange


inline bool inRange(unsigned int x)								// inRange (unsigned int)
{
	return true;
} // end function inRange