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

#ifndef OPENGL_ENGINE_H
#define OPENGL_ENGINE_H

// includes
#include <gl/glut.h>

namespace OpenGL
{

class Engine
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Engine(GLdouble left , GLdouble right , GLdouble bottom , GLdouble top)						// Engine default constructor
	{
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(left,right,bottom,top);
		glPushMatrix();	// so that it can be popped to restore the projection
						// matrix to the default without calling gluOrtho2D again

		// antialiasing and blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	} // end Engine default constructor

	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/

private:

	/***************
	* data members *
	***************/

}; // end class Engine

}; // end namespace OpenGL

#endif // OPENGL_ENGINE_H