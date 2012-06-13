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

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include "Vector2D.h"

template<typename StoredType = double>
struct Vector3D : public Vector2D<StoredType>
{

	/***************************
	* contructors & destructor *
	***************************/

	inline Vector3D()															// Vector3D default constructor
	{
		// do nothing
	} // end Vector3D default constructor


	inline Vector3D(const Vector3D &original)									// Vector3D copy constructor
		:Vector2D(original),z(original.z)
	{
		// empty body
	} // end Vector3D copy constructor


	inline Vector3D(StoredType X , StoredType Y , StoredType Z)					// Vector3D constructor
		:Vector2D(X,Y),z(Z)
	{
		// empty body
	} // end Vector3D conversion constructor


	inline ~Vector3D()															// Vector3D destructor
	{
		// empty body
	} // end Vector3D destructor




					/************
					* operators *
					************/

	inline Vector3D &operator = (const Vector3D &original)							// operator =
	{
		x = original.x;
		y = original.y;
		z = original.z;
		return *this;
	} // end function operator =


	inline bool operator == (const Vector3D &right) const							// operator ==
	{
		return x == right.x && y == right.y && z == right.z;
	} // end function operator ==


	inline bool operator != (const Vector3D &right) const							// operator !=
	{
		return !(*this == right);
	} // end function operator !=


				/*******************
				* member functions *
				*******************/

	inline Vector3D &setZ(StoredType Z)												// setZ
	{
		z = Z;
		return *this;
	} // end function setZ


	inline StoredType norm() const													// norm
	{
		return std::sqrt(x*x+y*y+z*z);
	} // end function norm



	/***************
	* data members *
	***************/

	StoredType z;

}; // end class Vector3D

#include "Vector3D/operators.h"

#endif // VECTOR3D_H