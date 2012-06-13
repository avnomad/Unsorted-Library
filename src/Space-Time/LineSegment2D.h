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

#ifndef LINE_SEGMENT_2D_H
#define LINE_SEGMENT_2D_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include <exceptions/exceptions.h>
#endif

#include <Space-Time/Vector2D.h>

template<typename StoredType>
inline bool inRange(const Vector2D<StoredType> &point , const Vector2D<StoredType> &end1 , const Vector2D<StoredType> &end2 , StoredType distance2)		// inRange
{														// distance2 is the square of distance.
	Vector2D<StoredType> u = end1 - end2;
	Vector2D<StoredType> r = point - end2;
	if(u*r >= 0 && u*(point-end1) <= 0)
	{
		StoredType nom = r % u;
		nom *= nom;
		StoredType den = u * u;
		if(den == 0) return false;
		if(nom/den < distance2) return true;
	} // end if
	return false;
} // end function inRange


#endif // LINE_SEGMENT_2D_H