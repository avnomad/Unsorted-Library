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

#include "Exceptions.h"
#include <windows.h>

void ExceptionMessageBox(const std::exception &e , const ExceptionExtension &ee , const char *caption)			// ExceptionMessageBox
{
	MessageBox(0,(std::string()+e.what()+" exception was thrown by "+ee.library()+" function "+ee.function()+".\n\n"+ee.details()).c_str(),caption,MB_ICONERROR);
} // end function ExceptionMessageBox
