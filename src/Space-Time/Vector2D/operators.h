// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include "../exceptions/Exceptions.h"
#endif


template<typename StoredType>
inline StoredType operator * (const Vector2D<StoredType> &left , const Vector2D<StoredType> &right)				// operator * (dot product)
{
	return left.x*right.x + left.y*right.y;
} // end function operator * (dot product)


template<typename StoredType , typename ArgType>
inline Vector2D<StoredType> operator * (ArgType left , const Vector2D<StoredType> &right)						// operator * (scalar product)
{
	return Vector2D<StoredType>(left*right.x , left*right.y);
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Vector2D<StoredType> operator * (const Vector2D<StoredType> &left , ArgType right)						// operator * (scalar product)
{
	return Vector2D<StoredType>(left.x*right , left.y*right);
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Vector2D<StoredType> operator / (const Vector2D<StoredType> &left , ArgType right)						// operator / (division by scalar)
{
	return Vector2D<StoredType>(left.x/right , left.y/right);
} // end function operator / (division by scalar)


template<typename StoredType>
inline StoredType operator % (const Vector2D<StoredType> &left , const Vector2D<StoredType> &right)				// operator % (cross product)
{
	return left.x*right.y - left.y*right.x;
} // end function operator % (cross product)


template<typename StoredType>
inline Vector2D<StoredType> operator + (const Vector2D<StoredType> &right)										// operator + (unary)
{
	return Vector2D<StoredType>(right);
} // end function operator + (unary)


template<typename StoredType>
inline Vector2D<StoredType> operator - (const Vector2D<StoredType> &right)										// operator - (unary)
{
	return Vector2D<StoredType>(-right.x , -right.y);
} // end function operator - (unary)


template<typename StoredType>
inline Vector2D<StoredType> operator + (const Vector2D<StoredType> &left , const Vector2D<StoredType> &right)	// operator + (binary)
{
	return Vector2D<StoredType>(left.x+right.x , left.y+right.y);
} // end function operator + (binary)


template<typename StoredType>
inline Vector2D<StoredType> operator - (const Vector2D<StoredType> &left , const Vector2D<StoredType> &right)	// operator - (binary)
{
	return Vector2D<StoredType>(left.x-right.x , left.y-right.y);
} // end function operator - (binary)


template<typename StoredType>
inline Vector2D<StoredType> &operator += (Vector2D<StoredType> &left , const Vector2D<StoredType> &right)		// operator +=
{
	left.x += right.x;
	left.y += right.y;
	return left;
} // end function operator +=


template<typename StoredType>
inline Vector2D<StoredType> &operator -= (Vector2D<StoredType> &left , const Vector2D<StoredType> &right)		// operator -=
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
} // end function operator -=


template<typename StoredType , typename ArgType>
inline Vector2D<StoredType> &operator *= (Vector2D<StoredType> &left , ArgType right)							// operator *=
{
	left.x *= right;
	left.y *= right;
	return left;
} // end function operator *=


template<typename StoredType , typename ArgType>
inline Vector2D<StoredType> &operator /= (Vector2D<StoredType> &left , ArgType right)							// operator /=
{
	left.x /= right;
	left.y /= right;
	return left;
} // end function operator /=


template<typename StoredType>
inline StoredType operator ^ (const Vector2D<StoredType> &left , const Vector2D<StoredType> &right)				// operator ^ (the angle of the 2 vectors in rads)
{
	StoredType temp = left*left;
	temp *= right*right;
	temp = std::sqrt(temp);

#ifdef DEBUG
	if(!temp) throw DivideByZeroException("A DivideByZeroException","ASL","Vector2D::operator ^",
		"An attempt was made to divide by zero in the above function.\nThis should be due to supplying the zero vector as an argument.");
#endif
	temp = (left*right)/temp;
#ifdef DEBUG
	if(temp > 1 || temp < -1) throw RuntimeError("A InvalidCosine","ASL","Vector2D::operator ^",
		"The number which was supposed to be the cosine of the angle\nwas outside the range [-1,1]. This should be due to arithmetic errors.");
#endif
	if(left%right < 0)
		return -std::acos(temp);
	else
		return std::acos(temp);
} // end function operator ^ (the angle of the 2 vectors in rads)
