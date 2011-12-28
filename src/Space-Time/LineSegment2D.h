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