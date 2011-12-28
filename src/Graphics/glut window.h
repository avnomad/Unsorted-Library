#ifndef GLUT_WINDOW_H
#define GLUT_WINDOW_H

#include <gl/freeglut.h>
#include <windows/common.h>


namespace GLUT
{

class Window
{
public:

	/***************************
	* contructors & destructor *
	***************************/



	inline Window(const Window &original)															// Window copy constructor
		:iWidth(original.iWidth),iHeight(original.iHeight),iHandle(original.iHandle)
	{
		// empty body
	} // end Window copy constructor


	// creates a standard window for a fullscreen
	// application using RGBA and double buffering.
	Window(const char *name);																		// Window conversion constructor


	inline ~Window()																				// Window destructor
	{
	} // end Window destructor




	/************
	* operators *
	************/

	inline Window &operator = (const Window &original)							// operator =
	{
		iHandle = original.iHandle;
		iWidth = original.iWidth;
		iHeight = original.iHeight;
		return *this;
	} // end function operator =


	inline bool operator == (const Window &right) const							// operator ==
	{
		return iHandle == right.iHandle;
	} // end function operator ==


	inline bool operator != (const Window &right) const							// operator !=
	{
		return iHandle != right.iHandle;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/


	inline WindowHandle getHandle()												// getHandle
	{
		return iHandle;
	} // end function getHandle


	inline int getWidth()														// getWidth
	{
		return iWidth;
	} // end function getWidth


	inline int getHeight()														// getHeight
	{
		return iHeight;
	} // end function getHeight


	inline void swapBuffers()													// swapBuffers
	{
		SwapBuffers(gdiContext);
	} // end function swapBuffers

private:

	/***************
	* data members *
	***************/

	WindowHandle iHandle;
	int iWidth;
	int iHeight;
	HDC gdiContext;
}; // end class Window

}; // end namespace GLUT

#endif // GLUT_WINDOW_H