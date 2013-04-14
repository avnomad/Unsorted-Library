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

#include "wavelength to RGB.h"

float spectrumRed(float wavelength)
{
	if(wavelength < 435)
		return (wavelength-435)/(380-435);
	else if(wavelength < 510)
		return 0;
	else if(wavelength < 580)
		return (wavelength-510)/(580-510);
	else
		return 1;
} // end function spectrumRed


float spectrumGreen(float wavelength)
{
	if(wavelength < 435)
		return 0;
	else if(wavelength < 485)
		return (wavelength-435)/(485-435);
	else if(wavelength < 580)
		return 1;
	else if(wavelength < 640)
		return (wavelength-640)/(580-640);
	else
		return 0;
} // end function spectrumGreen


float spectrumBlue(float wavelength)
{
	if(wavelength < 485)
		return 1;
	else if(wavelength < 510)
		return (wavelength-510)/(485-510);
	else
		return 0;
} // end function spectrumBlue