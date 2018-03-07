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

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

// includes
#include "triple.h"


		/*	copies from the range [iBegin,iEnd) to the range starting at oBegin until	*
		 *	the sequence in [sBegin,sEnd] is encountered or until the end of the input	*
		 *	range, whichever comes first.												*
		 *																				*
		 *	Preconditions:	sBegin should be != sEnd and the output target should be	*
		 *	of sufficient size.															*
		 *																				*
		 *	Value:	returns a Triple with the position after the last element read from	*
		 *	input, the position after the last element written to output and whether	*
		 *	the given sequence was encountered.											*
		 *																				*/

		// Note:	this version can't find the sequence if it is preceded by a prefix
		//			of itself...


template<typename IIter , typename OIter , typename FIter>
Triple<IIter,OIter,bool> copy_until_sequence(IIter iBegin , IIter iEnd , OIter oBegin , FIter sBegin , FIter sEnd)			// copy_until_sequence
{
	FIter sCurrent = sBegin;

	while(iBegin != iEnd)
	{
		if(*iBegin == *sCurrent)
		{
			++sCurrent;
			if(sCurrent == sEnd)
				return Triple<IIter,OIter,bool>(++iBegin,oBegin,true);
		}
		else
		{
			oBegin = std::copy(sBegin,sCurrent,oBegin);
			sCurrent = sBegin;
			*oBegin = *iBegin;
			++oBegin;
		} // end if-else
		++iBegin;
	} // end while

	return Triple<IIter,OIter,bool>(iBegin,oBegin,false);
} // end function template copy_until_sequence


#include <Space-Time/Vector2D.h>
#include <gl/glut.h>

template<typename IIter>
inline void displayString(IIter begin , IIter end)																			// displayString
{
	while(begin != end)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*begin) , ++begin;
} // end function displayString


template<typename IIter>
inline void displayString(IIter begin)																						// displayString
{
	while(*begin)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*begin) , ++begin;
} // end function displayString


template<typename CoordType , typename IIter>	// angle in degrees!
void displayString(const Vector2D<CoordType> &position , double height , double ratio , double angle , IIter begin , IIter end)	// displayString
{
	glPushMatrix();	// store the current matrix so that you may restore it later.
		// (after the local transformations, the transformations active at the time of the call will be applied.)
	glTranslated(position.x,position.y,0);	// at last, move the string to the specified location.
	glRotated(angle,0,0,1);	// then rotate the string
	double temp = height/152.38;	// calculate the scaling factor
	glScaled(temp*ratio,temp,1);	// first adjust the height and width of the characters.
	while(begin != end)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*begin) , ++begin;
	glPopMatrix();	// restore the transform matrix that was active at the time of the call.
} // end function displayString


template<typename CoordType , typename IIter>
void displayString(const Vector2D<CoordType> &position , double height , double ratio , double angle , IIter begin)			// displayString
{
	glPushMatrix();	// store the current matrix so that you may restore it later.
		// (after the local transformations, the transformations active at the time of the call will be applied.)
	glTranslated(position.x,position.y,0);	// at last, move the string to the specified location.
	glRotated(angle,0,0,1);	// then rotate the string
	double temp = height/152.38;	// calculate the scaling factor
	glScaled(temp*ratio,temp,1);	// first adjust the height and width of the characters.
	while(*begin)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*begin) , ++begin;
	glPopMatrix();	// restore the transform matrix that was active at the time of the call.
} // end function displayString


template<typename IIter>
inline int stringLenght(IIter begin , IIter end)																			// stringLenght
{
	int sum = 0;
	while(begin != end)
		sum += glutStrokeWidth(GLUT_STROKE_ROMAN,*begin) , ++begin;
	return sum;
} // end function stringLenght


template<typename FIter , typename FuncType , typename ArgType>
inline void apply(FIter begin , FIter end , FuncType f , ArgType arg)																// apply
{
	while(begin != end)
		f(*begin,arg) , ++begin;
} // end function apply


template<typename IIter , typename StoredType , typename ValueType>
inline void execute(IIter begin , IIter end , ValueType (StoredType::*method)())													// execute
{
	while(begin != end)
		((*begin).*method)() , ++begin;
} // end function execute


template<typename IIter , typename StoredType , typename ValueType , typename FuncArgType , typename ArgType>
inline void execute(IIter begin , IIter end , ValueType (StoredType::*method)(FuncArgType) , ArgType arg)							// execute
{
	while(begin != end)
		((*begin).*method)(arg) , ++begin;
} // end function execute


template<typename IIter , typename StoredType , typename ValueType , typename ArgType1 , typename ArgType2>
inline void execute(IIter begin , IIter end , ValueType (StoredType::*method)(ArgType1,ArgType2) , ArgType1 arg1 , ArgType2 arg2)	// execute
{
	while(begin != end)
		((*begin).*method)(arg1,arg2) , ++begin;
} // end function execute


template<typename IIter , typename StoredType , typename ValueType>
inline void execute_indirect(IIter begin , IIter end , ValueType (StoredType::*method)())									// execute_indirect
{
	while(begin != end)
		((*begin)->*method)() , ++begin;
} // end function execute_indirect


template<typename IIter , typename StoredType , typename ValueType , typename FuncArgType , typename ArgType>
inline void execute_indirect(IIter begin , IIter end , ValueType (StoredType::*method)(FuncArgType) , ArgType arg)			// execute_indirect
{
	while(begin != end)
		((*begin)->*method)(arg) , ++begin;
} // end function execute_indirect


template<typename IIter , typename OIter>
inline OIter cyclic_difference(IIter iBegin , IIter iEnd , OIter oBegin)													// cyclic_difference
{
	typename IIter::value_type firstValue,oldValue,newValue;

	if(iBegin == iEnd) return oBegin;

	firstValue = *iBegin;
	oldValue = firstValue;
	++iBegin;
	while(iBegin != iEnd)
	{
		newValue = *iBegin;
		++iBegin;
		*oBegin = newValue - oldValue;
		++oBegin;
		oldValue = newValue;
	} // end while
	*oBegin = firstValue - oldValue;

	return ++oBegin;
} // end function cyclic_difference


template<typename IIter , typename OIter , typename Func>
inline OIter cyclic_difference(IIter iBegin , IIter iEnd , OIter oBegin , Func f)											// cyclic_difference
{
	typename IIter::value_type firstValue,oldValue,newValue;

	if(iBegin == iEnd) return oBegin;

	firstValue = *iBegin;
	oldValue = firstValue;
	++iBegin;
	while(iBegin != iEnd)
	{
		newValue = *iBegin;
		++iBegin;
		*oBegin = f(newValue,oldValue);
		++oBegin;
		oldValue = newValue;
	} // end while
	*oBegin = f(firstValue,oldValue);

	return ++oBegin;
} // end function cyclic_difference


#include <vector>
#include <iterator>
// expects iterators pointing to Vector2Ds
template<typename IIter>
int fillable(IIter begin , IIter end)																						// fillable
{
	std::vector<typename IIter::value_type> v;
	int n,c;
	typename IIter::value_type::stored_type temp;
	

	cyclic_difference(begin,end,std::back_inserter(v));	// convert the sequence of vertices 
	n = v.size();									// given to a sequence of directed edges.
	if(n < 3) return 0;	// less than 3 vertices do not define a polygon.

	c = 1;
	while((temp = v[c-1] % v[c]) == 0 && ++c < n);
	if(c == n) return 0;
	
	if(temp > 0)
	{
		while(++c < n)
			if(v[c-1] % v[c] < 0) return 0;
		if(v[n-1] % v[0] < 0) return 0;			
		else return 1;
	}
	else
	{
		while(++c < n)
			if(v[c-1] % v[c] > 0) return 0;
		if(v[n-1] % v[0] > 0) return 0;			
		else return -1;
	} // end else
} // end function fillable


#include <utility>
/*
 * the first 2 iterators should be input iterators pointing to elements that can be passed to the unary predicate
 * function passed as the 5th argument. The 3rd and 4th arguments should be output iterators (not necessarily of
 * the same type) that point to containers supporting the insert method (all the first class containers qualify).
 * This algorithm splits the elements in the range [iBegin,iEnd) in 2 sets: those that satisfy the predicate f,
 * and those that don't. The difference from the split algorithm is that this algorithm puts ranges of satisfying
 * elements separated by a range of non-satisfying elements in subsequent containers in the range of containers
 * specified by tBegin, instead of putting them all in a single container. Similarly 2 ranges of non-satisfying
 * elements separated by a range of satisfying elements will be but in subsequent containers of the range specified
 * by fBegin. Both tBegin and fBegin should be pointing in containers of containers of sufficient size.
 */ 

template<typename IIter , typename OIter1 , typename OIter2 , typename FuncType>
std::pair<OIter1,OIter2> split_and_segment(IIter iBegin , IIter iEnd , OIter1 tBegin , OIter2 fBegin , FuncType f)			// split_and_segment
{
	if(iBegin == iEnd)
		goto function_end;
	else
		if(f(*iBegin))
			goto first_true;
		else
			goto first_false;

	do{
		if(f(*iBegin))
first_true:
			tBegin->insert(tBegin->end(),*iBegin);	// should I use insert(tBegin->end()) instead?
		else
		{
			++tBegin;
			goto first_false;
		} // end else
		++iBegin;
	}while(iBegin != iEnd);
	++tBegin;

	goto function_end;

	do{
		if(!f(*iBegin))
first_false:
			fBegin->insert(fBegin->end(),*iBegin);
		else
		{
			++fBegin;
			goto first_true;
		} // end else;
		++iBegin;
	}while(iBegin != iEnd);
	++fBegin;

function_end:
	return std::pair<OIter1,OIter2>(tBegin,fBegin);
} // end function split_and_segment


template<typename IIter1 , typename IIter2 , typename OIter1 , typename OIter2 , typename FuncType>
std::pair<OIter1,OIter2> split_and_segment(IIter1 dBegin , IIter1 dEnd , IIter2 iBegin , OIter1 tBegin , OIter2 fBegin , FuncType f)	// split_and_segment
{
	if(dBegin == dEnd)
		goto function_end;
	else
		if(f(*dBegin))
			goto first_true;
		else
			goto first_false;

	do{
		if(f(*dBegin))
first_true:
			tBegin->insert(tBegin->end(),*iBegin);
		else
		{
			++tBegin;
			goto first_false;
		} // end else
		++iBegin , ++dBegin;
	}while(dBegin != dEnd);
	++tBegin;

	goto function_end;

	do{
		if(!f(*dBegin))
first_false:
			fBegin->insert(fBegin->end(),*iBegin);
		else
		{
			++fBegin;
			goto first_true;
		} // end else;
		++iBegin , ++dBegin;
	}while(dBegin != dEnd);
	++fBegin;

function_end:
	return std::pair<OIter1,OIter2>(tBegin,fBegin);
} // end function split_and_segment


template<typename IIter , typename OIter , typename StoredType , typename ValueType>
OIter mapm(IIter iBegin , IIter iEnd , OIter oBegin , ValueType (StoredType::*method)() const)											// mapm
{
	while(iBegin != iEnd)
	{
		*oBegin = ((*iBegin).*method)();
		++oBegin , ++ iBegin;
	} // end while

	return oBegin;
} // end function mapm


template<typename IIter , typename OIter , typename StoredType , typename ValueType , typename ArgType1>
OIter mapm(IIter iBegin , IIter iEnd , OIter oBegin , ValueType (StoredType::*method)(ArgType1) const , ArgType1 arg1)					// mapm
{
	while(iBegin != iEnd)
	{
		*oBegin = ((*iBegin).*method)(arg1);
		++oBegin , ++ iBegin;
	} // end while

	return oBegin;
} // end function mapm

#ifdef min
#undef min
#endif

template<typename ContType>
typename ContType::value_type min(const ContType &container)																// min
{
	return *std::min_element(container.begin(),container.end());
} // end function min

#endif // ALGORITHMS_H
