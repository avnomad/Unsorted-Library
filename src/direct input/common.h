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

#ifndef DIRECT_INPUT_COMMON_H
#define DIRECT_INPUT_COMMON_H


#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// includes
#include <dinput.h>
#include <string>


std::string read_control_type(DWORD type);
std::string read_guid_type(const GUID &type);
std::string read_data_format_flags(DWORD flags);
std::string read_device_type(unsigned char type);
std::string read_device_subtype(WORD type_and_subtype);

#endif // DIRECT_INPUT_COMMON_H
