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

#ifndef STROKE_POINT_H
#define STROKE_POINT_H

// includes
#include <Space-Time/Vector2D.h>
#include <Space-Time/TimePoint.h>

template<typename StoredType = double>
struct StrokePoint : public Vector2D<StoredType> , public TimePoint<StoredType>
{
	typedef StoredType stored_type;

	/***************************
	* contructors & destructor *
	***************************/

	inline StrokePoint()															// StrokePoint default constructor
	{
		// empty body
	} // end StrokePoint default constructor


	inline StrokePoint(const StrokePoint &original)									// StrokePoint copy constructor
		:Vector2D(original),TimePoint(original),
		xTilt(original.xTilt),yTilt(original.yTilt),
		pressure(original.pressure),rotation(original.rotation)
	{
		// empty body
	} // end StrokePoint copy constructor


	inline StrokePoint(StoredType x , StoredType y , StoredType t)					// StrokePoint constructor
		:Vector2D(x,y),TimePoint(t)
	{
		// empty body
	} // end StrokePoint constructor


	inline StrokePoint(const Vector2D<StoredType> &point , StoredType t)			// StrokePoint constructor
		:Vector2D(point),TimePoint(t)
	{
		// empty body
	} // end StrokePoint constructor


	inline ~StrokePoint()															// StrokePoint destructor
	{
		// empty body
	} // end StrokePoint destructor




	/************
	* operators *
	************/

	inline StrokePoint &operator = (const StrokePoint &original)					// operator =
	{
		x = original.x;
		y = original.y;
		t = original.t;
		xTilt = original.xTilt;
		yTilt = original.yTilt;
		pressure = original.pressure;
		rotation = original.rotation;
		return *this;
	} // end function operator =


	bool operator == (const StrokePoint &right) const								// operator ==
	{
		return *this == (Vector2D<StoredType> &)original &&
			*this == (TimePoint<StoredType> &)original &&
			xTilt == right.xTilt && yTilt == right.yTilt &&
			pressure == right.pressure && rotation == right.rotation;
	} // end function operator ==


	inline bool operator != (const StrokePoint &right) const						// operator !=
	{
		return !(*this == right);
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline StrokePoint &setXTilt(StoredType tilt)									// setXTilt
	{
		xTilt = tilt;
		return *this;
	} // end function setXTilt


	inline StrokePoint &setYTilt(StoredType tilt)									// setYTilt
	{
		yTilt = tilt;
		return *this;
	} // end function setYTilt


	inline StrokePoint &setPressure(StoredType tipPressure)							// setPressure
	{
		pressure = tipPressure;
		return *this;
	} // end function setPressure


	inline StrokePoint &setRotation(StoredType barrelRotation)						// setRotation
	{
		rotation = barrelRotation;
		return *this;
	} // end function setRotation



	/***************
	* data members *
	***************/

	StoredType xTilt;
	StoredType yTilt;
	StoredType pressure;
	StoredType rotation;

}; // end class StrokePoint

#endif // STROKE_POINT_H