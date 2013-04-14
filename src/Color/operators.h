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

template<typename StoredType , typename ArgType>
inline Color<StoredType> operator * (ArgType left , const Color<StoredType> &right)						// operator * (scalar product)
{
	return Color<StoredType>(left*right.getRed() , left*right.getGreen() , left*right.getBlue() , right.getAlpha());
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Color<StoredType> operator * (const Color<StoredType> &left , ArgType right)						// operator * (scalar product)
{
	return Color<StoredType>(left.getRed()*right , left.getGreen()*right , left.getBlue()*right , left.getAlpha());
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Color<StoredType> operator / (const Color<StoredType> &left , ArgType right)						// operator / (division by scalar)
{
	return Color<StoredType>(left.getRed()/right , left.getGreen()/right , left.getBlue()/right , left.getAlpha());
} // end function operator / (division by scalar)


template<typename StoredType , typename ArgType>
inline Color<StoredType> &operator *= (Color<StoredType> &left , ArgType right)							// operator *=
{
	left.setRed(left.getRed() * right);
	left.setGreen(left.getGreen() * right);
	left.setBlue(left.getBlue() * right);
	return left;
} // end function operator *=


template<typename StoredType , typename ArgType>
inline Color<StoredType> &operator /= (Color<StoredType> &left , ArgType right)							// operator /=
{
	left.setRed(left.getRed() / right);
	left.setGreen(left.getGreen() / right);
	left.setBlue(left.getBlue() / right);
	return left;
} // end function operator /=
