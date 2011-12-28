#ifndef ROTATION_INDICATOR_H
#define ROTATION_INDICATOR_H

#ifndef PI
#define PI 3.141592653589793238462643383279502884197
#endif

#include <cmath>
#include "DisplayList.h"
#include <graphics/QuadricSurfaceDescriptor.h>
#include "../Space-Time/Vector2D.h"

class RotationIndicator : public DisplayList
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline RotationIndicator()															// RotationIndicator default constructor
	{
		// do nothing (the object must be initialized later by the compile mehtod).
	} // end RotationIndicator default constructor


	inline RotationIndicator(GLdouble innerRadius , GLdouble outerRadius)				// RotationIndicator constructor
	{
		compile(innerRadius,outerRadius);
	} // end RotationIndicator constructor



	/************
	* operators *
	************/


	/*******************
	* member functions *
	*******************/

	RotationIndicator &compile(GLdouble innerRadius , GLdouble outerRadius)				// compile
	{
		GLdouble temp,outerX,innerX,outerY,innerY,meanX,meanY;	// temporary variables

		iInnerRadius = innerRadius;	// store the inner and outer radii
		iOuterRadius = outerRadius;	// for use by other methods

		temp = (outerRadius-innerRadius)*2/5;
		outerRadius += temp;
		innerRadius -= temp;

		temp = std::cos(5*PI/12);	// calculate the cosine of the angle
		outerX = outerRadius*temp;	// then use it to calculate the outer
		innerX = innerRadius*temp;	// and inner Xs.

		temp = std::sin(5*PI/12);	// calculate the sine of the angle
		outerY = outerRadius*temp;	// then use it to calculate the outer
		innerY = innerRadius*temp;	// and inner Ys.

		temp = (outerRadius+innerRadius)/2; // calculate the average of the 2 radii
		meanX = temp*cos(16*PI/36);	// calculate the mean X
		meanY = temp*sin(16*PI/36);	// and Y.

		glNewList(iList,GL_COMPILE);
			glPushAttrib(GL_LINE_BIT);	// save line attributes
			glEnable(GL_LINE_SMOOTH);	// enable antialiasing
			gluPartialDisk(SOLID,iInnerRadius,iOuterRadius,360,10,15,150);
			gluPartialDisk(SOLID,iInnerRadius,iOuterRadius,360,10,195,150);
			glBegin(GL_TRIANGLES);
				glVertex2d(innerX,innerY);
				glVertex2d(outerX,outerY);
				glVertex2d(meanX,meanY);

				glVertex2d(innerX,-innerY);
				glVertex2d(outerX,-outerY);
				glVertex2d(meanX,-meanY);

				glVertex2d(-innerX,innerY);
				glVertex2d(-outerX,outerY);
				glVertex2d(-meanX,meanY);

				glVertex2d(-innerX,-innerY);
				glVertex2d(-outerX,-outerY);
				glVertex2d(-meanX,-meanY);
			glEnd();
			glPopAttrib();	// restore line attributes
		glEndList();
		return *this;
	} // end function compile


	template<typename StoredType>
	inline bool inside(const Vector2D<StoredType> &point)								// inside
	{
		return point.norm() < iInnerRadius;
	} // end function inside


	template<typename StoredType>
	inline bool outside(const Vector2D<StoredType> &point)								// outside
	{
		return point.norm() > iOuterRadius;
	} // end function outside


	template<typename StoredType>
	inline bool over(const Vector2D<StoredType> &point)									// over
	{
		return iInnerRadius <= point.norm() && point.norm() <= iOuterRadius;
	} // end function over



private:

	/***************
	* data members *
	***************/

	GLdouble iInnerRadius;
	GLdouble iOuterRadius;

}; // end class RotationIndicator

#endif // ROTATION_INDICATOR_H