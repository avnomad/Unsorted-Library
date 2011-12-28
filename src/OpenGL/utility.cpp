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
