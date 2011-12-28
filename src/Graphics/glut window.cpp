#include "glut window.h"

// includes
#include <utility>

static int width;
static int height;

static void sizeNoter(int width , int height)										// sizeNoter
{
	::width = width;
	::height = height;
	glViewport(0,0,width,height);
	throw 0;
	//throw std::pair<int,int>(width,height);
} // end function sizeNoter


static void intThrower(void){
	throw 0;
	std::cout<<"hi!";
}												// intThrower


GLUT::Window::Window(const char *name)												// Window conversion constructor
{
	int argc = 1;	// trick glutInit.
	char *str = "GLUT_application";
	char **argv = &str;

	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);	// dummy values.
	glutInitWindowSize(32,32);		// dummy values.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// this should be appropriate
	glutCreateWindow(name);							// for most 3D applications.

	glutFullScreen();	// enter full screen mode

	glutDisplayFunc(intThrower);
	glutReshapeFunc(sizeNoter);		// the window doesn't show until we call
	try								// glutMainLoop and the display function
	{								// is called. To make things worse, the
		glutMainLoop();				// reshape function is called before the
	}								// display function and thus we use this
	catch(int)						// trick to make the window show leave
	{								// the loop and get the screen resolution
		// do nothing
	} // end catch

	iWidth = ::width;
	iHeight = ::height;

	iHandle = FindWindow(0,name);	// get the window handle of the created window.
} // end Window conversion constructor
