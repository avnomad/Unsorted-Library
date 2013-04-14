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

#ifndef UTILITY_H
#define UTILITY_H

// #defines
#ifndef Pi
#define Pi 3.14159265358979323846264338328
#endif

#ifndef Fi
#define Fi 1.61803398874989484820458683437
#endif

#ifndef e
#define e 2.71828182845904523536028747135
#endif

#include <cmath>

template<typename FloatingPointType>
inline FloatingPointType round(FloatingPointType x , FloatingPointType step)								// round
{
	return step*std::floor(x/step + 0.5);
} // end function round


#include <functional>

template<typename ThresholdType , typename ComparatorType = std::greater<ThresholdType> >
class Threshold																								// Threshold
{
public:
	inline Threshold(const ThresholdType &threshold)														// conversion constructor
		:iThreshold(threshold)
	{
		// empty body
	} // end Threshold conversion constructor

	inline Threshold(const Threshold &original)																// copy constructor
		:iThreshold(original.iThreshold)
	{
		// empty body
	} // end Threshold copy constructor

	inline bool operator()(const ThresholdType &valueInQuestion)											// function operator
	{
		return ComparatorType()(valueInQuestion,iThreshold);
	} // end function operator ()
private:
	ThresholdType iThreshold;
}; // end class Threshold


#include <gl/glut.h>
#include <Space-Time/Vector2D.h>

template<typename StoredType>
Vector2D<StoredType> unproject(const Vector2D<StoredType> &point)											// unproject
{
	GLdouble x,y,z;
	GLdouble projection[16];
	GLdouble modelview[16];
	GLint viewport[4];

	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetIntegerv(GL_VIEWPORT,viewport);

	if(GL_FALSE == gluUnProject(point.x,point.y,0,modelview,projection,viewport,&x,&y,&z))
		throw RuntimeError("An UnableToUnproject","glu","gluUnProject",
		"Unable to unproject point. This may be due to a not invertible projection matrix.");

	return Vector2D<StoredType>(x,y);
} // end function unproject

#endif // UTILITY_H