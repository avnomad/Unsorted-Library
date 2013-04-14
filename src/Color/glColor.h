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

#ifndef GLCOLOR_H
#define GLCOLOR_H

// includes
#include <gl/glut.h>
#include <Color.h>

inline void glColor(const RGBA::Color<signed char> &color)					// glColor (signed char)
{
	glColor4bv(color);
} // end function glColor


inline void glColor(const RGBA::Color<short> &color)							// glColor (short)
{
	glColor4sv(color);
} // end function glColor


inline void glColor(const RGBA::Color<int> &color)							// glColor (int)
{
	glColor4iv(color);
} // end function glColor


inline void glColor(const RGBA::Color<float> &color)							// glColor (float)
{
	glColor4fv(color);
} // end function glColor


inline void glColor(const RGBA::Color<double> &color)							// glColor (double)
{
	glColor4dv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned char> &color)					// glColor (unsigned char)
{
	glColor4ubv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned short> &color)					// glColor (unsigned short)
{
	glColor4usv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned int> &color)					// glColor (unsigned int)
{
	glColor4uiv(color);
} // end function glColor

#endif // GLCOLOR_H