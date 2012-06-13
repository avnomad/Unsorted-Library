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

#ifndef DIGITIZER_PROPERTIES_H
#define DIGITIZER_PROPERTIES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <windows/common.h>

struct DigitizerProperties
{
	/**************************
	* contructors & destructor*
	**************************/


	/************
	* operators *
	************/


	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	bool usesAbsoluteAxes;
	DWORD bufferSize;
	WORD VendorID;
	WORD ProductID;

	DWORD XAxisGranularity;
	DWORD YAxisGranularity;
	DWORD TipPressureGranularity;
	DWORD XTiltGranularity;
	DWORD YTiltGranularity;

	LONG XAxisLogicalMin;
	LONG XAxisLogicalMax;
	LONG YAxisLogicalMin;
	LONG YAxisLogicalMax;
	LONG TipPressureLogicalMin;
	LONG TipPressureLogicalMax;
	LONG XTiltLogicalMin;
	LONG XTiltLogicalMax;
	LONG YTiltLogicalMin;
	LONG YTiltLogicalMax;

	LONG XAxisPhysicalMin;
	LONG XAxisPhysicalMax;
	LONG YAxisPhysicalMin;
	LONG YAxisPhysicalMax;
	LONG TipPressurePhysicalMin;
	LONG TipPressurePhysicalMax;
	LONG XTiltPhysicalMin;
	LONG XTiltPhysicalMax;
	LONG YTiltPhysicalMin;
	LONG YTiltPhysicalMax;

	DWORD XAxisMin;
	DWORD XAxisMax;
	DWORD YAxisMin;
	DWORD YAxisMax;
	DWORD TipPressureMin;
	DWORD TipPressureMax;
	DWORD XTiltMin;
	DWORD XTiltMax;
	DWORD YTiltMin;
	DWORD YTiltMax;

	std::wstring portName;

}; // end struct DigitizerProperties

std::wostream &operator<<(std::wostream &outStream , const DigitizerProperties &properties)								// operator <<
{
	outStream << std::left << std::setw(30) << "Device axes in absolute mode:" << std::right << std::setw(27) << properties.usesAbsoluteAxes << '\n';
	outStream << std::left << std::setw(30) << "Vendor ID:" << std::right << std::setw(27) << properties.VendorID << '\n';
	outStream << std::left << std::setw(30) << "Product ID:" << std::right << std::setw(27) << properties.ProductID << '\n';
	outStream << std::left << std::setw(30) << "Buffer size:" << std::right << std::setw(25) << properties.bufferSize << "\n\n";

	outStream << std::left << std::setw(30) << "X axis granularity:" << std::right << std::setw(25) << properties.XAxisGranularity << '\n';
	outStream << std::left << std::setw(30) << "Y axis granularity:" << std::right << std::setw(25) << properties.YAxisGranularity << '\n';
	outStream << std::left << std::setw(30) << "Tip pressure granularity:" << std::right << std::setw(25) << properties.TipPressureGranularity << '\n';
	outStream << std::left << std::setw(30) << "X tilt granularity:" << std::right << std::setw(25) << properties.XTiltGranularity << '\n';
	outStream << std::left << std::setw(30) << "Y tilt granularity:" << std::right << std::setw(25) << properties.YTiltGranularity << "\n\n";

	outStream << std::left << std::setw(30) << "X axis logical range:" << std::right << std::setw(23) << properties.XAxisLogicalMin << " - " << std::left << std::setw(23) << properties.XAxisLogicalMax << '\n';
	outStream << std::left << std::setw(30) << "Y axis logical range:" << std::right << std::setw(23) << properties.YAxisLogicalMin << " - " << std::left << std::setw(23) << properties.YAxisLogicalMax << '\n';
	outStream << std::left << std::setw(30) << "Tip pressure logical range:" << std::right << std::setw(23) << properties.TipPressureLogicalMin << " - " << std::left << std::setw(23) << properties.TipPressureLogicalMax << '\n';
	outStream << std::left << std::setw(30) << "X tilt logical range:" << std::right << std::setw(23) << properties.XTiltLogicalMin << " - " << std::left << std::setw(23) << properties.XTiltLogicalMax << '\n';
	outStream << std::left << std::setw(30) << "Y tilt logical range:" << std::right << std::setw(23) << properties.YTiltLogicalMin << " - " << std::left << std::setw(23) << properties.YTiltLogicalMax << "\n\n";

	outStream << std::left << std::setw(30) << "X axis physical range:" << std::right << std::setw(23) << properties.XAxisPhysicalMin << " - " << std::left << std::setw(23) << properties.XAxisPhysicalMax << '\n';
	outStream << std::left << std::setw(30) << "Y axis physical range:" << std::right << std::setw(23) << properties.YAxisPhysicalMin << " - " << std::left << std::setw(23) << properties.YAxisPhysicalMax << '\n';
	outStream << std::left << std::setw(30) << "Tip pressure physical range:" << std::right << std::setw(23) << properties.TipPressurePhysicalMin << " - " << std::left << std::setw(23) << properties.TipPressurePhysicalMax << '\n';
	outStream << std::left << std::setw(30) << "X tilt physical range:" << std::right << std::setw(23) << properties.XTiltPhysicalMin << " - " << std::left << std::setw(23) << properties.XTiltPhysicalMax << '\n';
	outStream << std::left << std::setw(30) << "Y tilt physical range:" << std::right << std::setw(23) << properties.YTiltPhysicalMin << " - " << std::left << std::setw(23) << properties.YTiltPhysicalMax << "\n\n";

	outStream << std::left << std::setw(30) << "X axis range:" << std::right << std::setw(23) << properties.XAxisMin << " - " << std::left << std::setw(23) << properties.XAxisMax << '\n';
	outStream << std::left << std::setw(30) << "Y axis range:" << std::right << std::setw(23) << properties.YAxisMin << " - " << std::left << std::setw(23) << properties.YAxisMax << '\n';
	outStream << std::left << std::setw(30) << "Tip pressure range:" << std::right << std::setw(23) << properties.TipPressureMin << " - " << std::left << std::setw(23) << properties.TipPressureMax << '\n';
	outStream << std::left << std::setw(30) << "X tilt range:" << std::right << std::setw(23) << properties.XTiltMin << " - " << std::left << std::setw(23) << properties.XTiltMax << '\n';
	outStream << std::left << std::setw(30) << "Y tilt range:" << std::right << std::setw(23) << properties.YTiltMin << " - " << std::left << std::setw(23) << properties.YTiltMax << "\n\n";

	outStream << std::left << std::setw(30) << "Port name:" << std::right << std::setw(49) << properties.portName << '\n';
	return outStream;
} // end function operator <<

#endif // DIGITIZER_PROPERTIES_H
