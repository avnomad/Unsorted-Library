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

#ifndef VECTOR2D_H
#define VECTOR2D_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include <exceptions/exceptions.h>
#endif

#include <cmath>

template<typename StoredType = double>
struct Vector2D
{
	typedef StoredType stored_type;

	/***************************
	* contructors & destructor *
	***************************/

	inline Vector2D()															// Vector2D default constructor
	{
		// do nothing
	} // end Vector2D default constructor


	inline Vector2D(const Vector2D &original)									// Vector2D copy constructor
		:x(original.x),y(original.y)
	{
		// empty body
	} // end Vector2D copy constructor


	inline Vector2D(StoredType X , StoredType Y)								// Vector2D constructor
		:x(X),y(Y)
	{
		// empty body
	} // end Vector2D conversion constructor


	inline ~Vector2D()															// Vector2D destructor
	{
		// empty body
	} // end Vector2D destructor




					/************
					* operators *
					************/

	inline Vector2D &operator = (const Vector2D &original)							// operator =
	{
		x = original.x;
		y = original.y;
		return *this;
	} // end function operator =


	inline bool operator == (const Vector2D &right) const							// operator ==
	{
		return x == right.x && y == right.y;
	} // end function operator ==


	inline bool operator != (const Vector2D &right) const							// operator !=
	{
		return x != right.x || y != right.y;
	} // end function operator !=


	inline operator const StoredType * () const										// operator StoredType *
	{
		return &x;
	} // end function operator StoredType *


	inline operator StoredType * ()													// operator StoredType *
	{
		return &x;
	} // end function operator StoredType *


				/*******************
				* member functions *
				*******************/

	inline Vector2D &setX(StoredType X)												// setX
	{
		x = X;
		return *this;
	} // end function setX


	inline Vector2D &setY(StoredType Y)												// setY
	{
		y = Y;
		return *this;
	} // end function setY


	inline StoredType norm() const													// norm
	{
		return std::sqrt(x*x+y*y);
	} // end function norm


	inline StoredType norm2() const													// norm2
	{
		return x*x+y*y;
	} // end function norm


	inline StoredType normInf() const												// normInf
	{
		return std::max(fabs(x),fabs(y));
	} // end function normInf


	inline StoredType angle() const													// angle
	{
		return std::atan2(y,x);
	} // end function angle


	inline Vector2D projection(const Vector2D &destination) const					// projection
	{
		StoredType normSquare = destination*destination;
#ifdef DEBUG
		if(!normSquare) throw RuntimeError("A NullVector","ASL","Vector2D::projection",
			"Cannot project on the null vector!");
#endif
		return ((*this * destination) / normSquare) * destination;
	} // end function projection


	// maps this vector to the vector with the same magnitude which forms a +90
	// degree angle with this vector (perpendicular.angle()-this->angle() == PI/2)
	inline Vector2D perpendicular()													// perpendicular
	{
		return Vector2D(-y,x);
	} // end function perpendicular



	/***************
	* data members *
	***************/

	StoredType x;
	StoredType y;

}; // end class Vector2D

#include "Vector2D/operators.h"

#endif // VECTOR2D_H