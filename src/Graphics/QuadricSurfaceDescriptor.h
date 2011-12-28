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