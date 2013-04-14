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

#ifndef WINDOWS_COMMON_H
#define WINDOWS_COMMON_H

// includes
#include <iostream>
#include <windows.h>
#include <TCHAR.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifdef socket
#undef socket
#endif

// make windows.h names prettier!
#define InstanceHandle HINSTANCE
#define WindowHandle HWND
#define ResultHandle HRESULT

// protorypes
std::ostream &operator<<(std::ostream & , const GUID &);

#endif // WINDOWS_COMMON_H
