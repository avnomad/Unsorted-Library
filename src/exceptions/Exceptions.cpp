#include "Exceptions.h"
#include <windows.h>

void ExceptionMessageBox(const std::exception &e , const ExceptionExtension &ee , const char *caption)			// ExceptionMessageBox
{
	MessageBox(0,(std::string()+e.what()+" exception was thrown by "+ee.library()+" function "+ee.function()+".\n\n"+ee.details()).c_str(),caption,MB_ICONERROR);
} // end function ExceptionMessageBox
