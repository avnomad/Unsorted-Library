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