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

#ifndef QUADRIC_SURFACE_DESCRIPTOR_H
#define QUADRIC_SURFACE_DESCRIPTOR_H

#include <gl/glut.h>

class QuadricSurfaceDescriptor
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline QuadricSurfaceDescriptor()															// QuadricSurfaceDescriptor default constructor
		:iQuadric(gluNewQuadric())
	{
		// empty body
	} // end QuadricSurfaceDescriptor default constructor


	inline QuadricSurfaceDescriptor(GLUquadric *Quadric)										// QuadricSurfaceDescriptor conversion constructor
		:iQuadric(Quadric)
	{
		// empty body
	} // end QuadricSurfaceDescriptor constructor


	inline QuadricSurfaceDescriptor(GLenum surfaceDrawStyle)									// QuadricSurfaceDescriptor constructor
		:iQuadric(gluNewQuadric())
	{
		gluQuadricDrawStyle(iQuadric,surfaceDrawStyle);
	} // end QuadricSurfaceDescriptor constructor

	inline ~QuadricSurfaceDescriptor()															// QuadricSurfaceDescriptor destructor
	{
		gluDeleteQuadric(iQuadric);
	} // end QuadricSurfaceDescriptor destructor



	/************
	* operators *
	************/

	inline operator GLUquadric *() const														// operator GLUquadric *
	{
		return iQuadric;
	} // end function operator GLUquadric *


	inline bool operator == (const QuadricSurfaceDescriptor &right) const						// operator ==
	{
		return iQuadric == right.iQuadric;
	} // end function operator ==


	inline bool operator != (const QuadricSurfaceDescriptor &right) const						// operator !=
	{
		return iQuadric != right.iQuadric;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

private:

	/***************
	* data members *
	***************/

	GLUquadric *iQuadric;

	inline QuadricSurfaceDescriptor(const QuadricSurfaceDescriptor &){}	// objects of this class should not be copied
	inline QuadricSurfaceDescriptor &operator = (const QuadricSurfaceDescriptor &){}
}; // end class QuadricSurfaceDescriptor

extern const QuadricSurfaceDescriptor SOLID;
extern const QuadricSurfaceDescriptor WIREFRAME;
extern const QuadricSurfaceDescriptor VERTICES;
extern const QuadricSurfaceDescriptor SILHOUETTE;

#endif // QUADRIC_SURFACE_DESCRIPTOR_H