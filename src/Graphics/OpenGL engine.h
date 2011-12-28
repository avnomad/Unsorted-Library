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