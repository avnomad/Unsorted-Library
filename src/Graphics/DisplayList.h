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

#ifndef DISPLAYLIST_H
#define DISPLAYLIST_H

#include <gl/glut.h>

class DisplayList
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline DisplayList()															// DisplayList default constructor
		:iList(glGenLists(1))
	{
		// empty body
	} // end DisplayList default constructor


	explicit inline DisplayList(GLuint list)										// DisplayList conversion constructor
		:iList(list)
	{
		// empty body
	} // end DisplayList constructor


	inline ~DisplayList()															// DisplayList destructor
	{
		glDeleteLists(iList,1);
	} // end DisplayList destructor



	/************
	* operators *
	************/



	inline bool operator == (const DisplayList &right) const						// operator ==
	{
		return this->iList == right.iList;
	} // end function operator ==


	inline bool operator != (const DisplayList &right) const						// operator !=
	{
		return this->iList != right.iList;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline const DisplayList &call() const											// call
	{
		glCallList(iList);
		return *this;
	} // end function call

protected:

	/***************
	* data members *
	***************/

	GLuint iList;

private:
	inline DisplayList(const DisplayList &){}	// objects of this class should not be copied
	inline DisplayList &operator = (const DisplayList &){}
}; // end class DisplayList

#endif // DISPLAYLIST_H