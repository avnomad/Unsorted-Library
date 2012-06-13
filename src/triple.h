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

#ifndef TRIPLE_H
#define TRIPLE_H

template<typename T1 , typename T2 , typename T3>
struct Triple
{
	// typedefs
	typedef T1 first_type;
	typedef T2 second_type;
	typedef T3 third_type;

	// constructors
	Triple()																		// default constructor
	{
		// empty body (the default constructors
		// for the data members will be called)
	} // end Triple default constructor

	template<typename O1 , typename O2 , typename O3> // other (compatible) type
	Triple(const Triple<O1,O2,O3> &original)										// copy constructor
		:first(original.first),second(original.second),third(original.third)
	{
		// empty body
	} // end Triple copy constructor

	Triple(const T1 &firstValue , const T2 &secondValue , const T3 &thirdValue)		// constructor
		:first(firstValue),second(secondValue),third(thirdValue)
	{
		// empty body
	} // end Triple constructor

	// operators
	Triple &operator=(const Triple&original)										// operator =
	{
		first = original.first;
		second = original.second;
		third = original.third;
		return *this;
	} // end fuction operator =

	// data members
	T1 first;	// the first stored value
	T2 second;	// the second stored value
	T3 third;	// the third stored value
}; // end class Triple

#endif // TRIPLE_H
	