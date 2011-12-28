#ifndef GLCOLOR_H
#define GLCOLOR_H

// includes
#include <gl/glut.h>
#include <Color.h>

inline void glColor(const RGBA::Color<signed char> &color)					// glColor (signed char)
{
	glColor4bv(color);
} // end function glColor


inline void glColor(const RGBA::Color<short> &color)							// glColor (short)
{
	glColor4sv(color);
} // end function glColor


inline void glColor(const RGBA::Color<int> &color)							// glColor (int)
{
	glColor4iv(color);
} // end function glColor


inline void glColor(const RGBA::Color<float> &color)							// glColor (float)
{
	glColor4fv(color);
} // end function glColor


inline void glColor(const RGBA::Color<double> &color)							// glColor (double)
{
	glColor4dv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned char> &color)					// glColor (unsigned char)
{
	glColor4ubv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned short> &color)					// glColor (unsigned short)
{
	glColor4usv(color);
} // end function glColor


inline void glColor(const RGBA::Color<unsigned int> &color)					// glColor (unsigned int)
{
	glColor4uiv(color);
} // end function glColor

#endif // GLCOLOR_H