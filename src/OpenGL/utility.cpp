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

#include "utility.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <GL/glew.h>

namespace GL
{

void printError()
{
	switch(glGetError())
	{
	case GL_NO_ERROR:
		break;
	case GL_INVALID_ENUM:
		cerr << "GL_INVALID_ENUM." << endl;
		break;
	case GL_INVALID_VALUE:
		cerr << "GL_INVALID_VALUE." << endl;
		break;
	case GL_INVALID_OPERATION:
		cerr << "GL_INVALID_OPERATION." << endl;
		break;
	case GL_STACK_OVERFLOW:
		cerr << "GL_STACK_OVERFLOW." << endl;
		break;
	case GL_STACK_UNDERFLOW:
		cerr << "GL_STACK_UNDERFLOW." << endl;
		break;
	case GL_OUT_OF_MEMORY:
		cerr << "GL_OUT_OF_MEMORY." << endl;
		break;
	case GL_TABLE_TOO_LARGE:
		cerr << "GL_TABLE_TOO_LARGE." << endl;
		break;
	} // end switch
} // end function printError


void printFramebufferCompletenessStatus()
{
	switch(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER))
	{
	case GL_FRAMEBUFFER_COMPLETE:
		cerr << "GL_FRAMEBUFFER_COMPLETE." << endl;
		break;
	case GL_FRAMEBUFFER_UNDEFINED:
		cerr << "GL_FRAMEBUFFER_UNDEFINED." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		cerr << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		cerr << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER." << endl;
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		cerr << "GL_FRAMEBUFFER_UNSUPPORTED." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		cerr << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE." << endl;
		break;
	case 0:
		cerr << "glCheckFramebufferStatus error." << endl;
		break;
	} // end switch
} // end function printFramebufferCompletenessStatus

}; // end namespace GL
