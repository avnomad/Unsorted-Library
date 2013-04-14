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

#ifndef GLVERTEX2_H
#define GLVERTEX2_H

// includes
#include <gl/glut.h>
#include <Space-Time/Vector2D.h>

inline void glVertex2(const Vector2D<short> &vertex)						// glVertex2 (short)
{
	glVertex2sv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<int> &vertex)							// glVertex2 (int)
{
	glVertex2iv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<float> &vertex)						// glVertex2 (float)
{
	glVertex2fv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<double> &vertex)						// glVertex2 (double)
{
	glVertex2dv(vertex);
} // end function glVertex2

#endif // GLVERTEX2_H