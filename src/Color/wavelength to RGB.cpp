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