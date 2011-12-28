#ifndef UTILITY_H
#define UTILITY_H

// #defines
#ifndef Pi
#define Pi 3.14159265358979323846264338328
#endif

#ifndef Fi
#define Fi 1.61803398874989484820458683437
#endif

#ifndef e
#define e 2.71828182845904523536028747135
#endif

#include <cmath>

template<typename FloatingPointType>
inline FloatingPointType round(FloatingPointType x , FloatingPointType step)								// round
{
	return step*std::floor(x/step + 0.5);
} // end function round


#include <functional>

template<typename ThresholdType , typename ComparatorType = std::greater<ThresholdType> >
class Threshold																								// Threshold
{
public:
	inline Threshold(const ThresholdType &threshold)														// conversion constructor
		:iThreshold(threshold)
	{
		// empty body
	} // end Threshold conversion constructor

	inline Threshold(const Threshold &original)																// copy constructor
		:iThreshold(original.iThreshold)
	{
		// empty body
	} // end Threshold copy constructor

	inline bool operator()(const ThresholdType &valueInQuestion)											// function operator
	{
		return ComparatorType()(valueInQuestion,iThreshold);
	} // end function operator ()
private:
	ThresholdType iThreshold;
}; // end class Threshold


#include <gl/glut.h>
#include <Space-Time/Vector2D.h>

template<typename StoredType>
Vector2D<StoredType> unproject(const Vector2D<StoredType> &point)											// unproject
{
	GLdouble x,y,z;
	GLdouble projection[16];
	GLdouble modelview[16];
	GLint viewport[4];

	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetIntegerv(GL_VIEWPORT,viewport);

	if(GL_FALSE == gluUnProject(point.x,point.y,0,modelview,projection,viewport,&x,&y,&z))
		throw RuntimeError("An UnableToUnproject","glu","gluUnProject",
		"Unable to unproject point. This may be due to a not invertible projection matrix.");

	return Vector2D<StoredType>(x,y);
} // end function unproject

#endif // UTILITY_H