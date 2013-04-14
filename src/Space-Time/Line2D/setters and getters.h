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

	/* setters */

inline Line2D &setA(StoredType A)												// setA
{
	iA = A;
	return *this;
} // end function setA


inline Line2D &setB(StoredType B)												// setB
{
	iB = B;
	return *this;
} // end function setB


inline Line2D &setC(StoredType C)												// setC
{
	iC = C;
	return *this;
} // end function setC


inline Line2D &setABC(StoredType A,StoredType B,StoredType C)					// setABC
{
	iA = A;
	iB = B;
	iC = C;
	return *this;
} // end function setABC



	/* getters */

inline StoredType getA() const													// getA
{
	return iA;
} // end function getA


inline StoredType getB() const													// getB
{
	return iB;
} // end function getB


inline StoredType getC() const													// getC
{
	return iC;
} // end function getC
