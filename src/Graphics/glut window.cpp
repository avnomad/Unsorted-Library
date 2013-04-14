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

#include "glut window.h"

// includes
#include <utility>

GLUT::Window::Window(const char *name)												// Window conversion constructor
{
	// initialize GLUT: still needed to call some glut functions
	int argc = 1;	// trick glutInit.
	char *str = "GLUT_application";
	char **argv = &str;
	glutInit(&argc,argv);

	// create OpenGL window the Win32 way
	WNDCLASS windowClass;
	ZeroMemory(&windowClass,sizeof(windowClass));
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = "defaultClass";
	windowClass.style = CS_OWNDC;

	RegisterClass(&windowClass);

	iHandle = CreateWindow("defaultClass",name,WS_POPUP,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
					nullptr,nullptr,GetModuleHandle(nullptr),nullptr);

	ShowWindow(iHandle,SW_NORMAL);
	ShowWindow(iHandle,SW_MAXIMIZE);
	UpdateWindow(iHandle);

	// get window dimentions
	RECT clientRectangle;
	GetClientRect(iHandle,&clientRectangle);
	iWidth = clientRectangle.right-clientRectangle.left;
	iHeight = clientRectangle.bottom-clientRectangle.top;

	this->gdiContext = GetDC(iHandle);
	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_STEREO_DONTCARE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cAccumBits = 0;
	pfd.cDepthBits = 0;
	pfd.cStencilBits = 0;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pixelFormatIndex = ChoosePixelFormat(gdiContext,&pfd);
	SetPixelFormat(gdiContext,pixelFormatIndex,&pfd);
	glContext = wglCreateContext(gdiContext);
	wglMakeCurrent(gdiContext,glContext);
} // end Window conversion constructor
