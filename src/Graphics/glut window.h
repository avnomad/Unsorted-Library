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

#ifndef GLUT_WINDOW_H
#define GLUT_WINDOW_H

#include <gl/glut.h>
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
		:iWidth(original.iWidth),iHeight(original.iHeight),iHandle(original.iHandle),
		gdiContext(original.gdiContext),glContext(original.glContext)
	{
		// empty body
	} // end Window copy constructor


	// creates a standard window for a fullscreen
	// application using RGBA and double buffering.
	Window(const char *name);																		// Window conversion constructor


	inline ~Window()																				// Window destructor
	{
		wglMakeCurrent(nullptr,nullptr);
		wglDeleteContext(glContext);
		// the device context is private and will be destroyed with the window.
		DestroyWindow(iHandle);
	} // end Window destructor




	/************
	* operators *
	************/

	inline Window &operator = (const Window &original)							// operator =
	{
		iHandle = original.iHandle;
		iWidth = original.iWidth;
		iHeight = original.iHeight;
		gdiContext = original.gdiContext;
		glContext = original.glContext;
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
	HGLRC glContext;
}; // end class Window

}; // end namespace GLUT

#endif // GLUT_WINDOW_H