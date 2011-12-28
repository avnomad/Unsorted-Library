#ifndef GLVERTEX2_H
#define GLVERTEX2_H

// includes
#include <gl/glut.h>
#include <Space-Time/Vector2D.h>

inline void glVertex2(const Vector2D<short> &vertex)						// glVertex2 (short)
{
	glVertex2sv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<int> &vertex)							// glVertex2 (int)
{
	glVertex2iv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<float> &vertex)						// glVertex2 (float)
{
	glVertex2fv(vertex);
} // end function glVertex2


inline void glVertex2(const Vector2D<double> &vertex)						// glVertex2 (double)
{
	glVertex2dv(vertex);
} // end function glVertex2

#endif // GLVERTEX2_H