#include "StopWatch.h"


				/**************
				* contructors *
				**************/

	StopWatch::StopWatch(const std::string &timeUnit)					// default constructor
		:iUnit(timeUnit)
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		if(!timeUnit.compare("ms"))		// fragments of second
			iMultiplier = 1e3;
		else if(!timeUnit.compare("ìs"))
			iMultiplier = 1e6;
		else if(!timeUnit.compare("ns"))
			iMultiplier = 1e9;
		else if(!timeUnit.compare("ps"))
			iMultiplier = 1e12;
		else if(!timeUnit.compare("ks"))	// multiples of second
			iMultiplier = 1e-3;
		else if(!timeUnit.compare("Ms"))
			iMultiplier = 1e-6;
		else if(!timeUnit.compare("Gs"))
			iMultiplier = 1e-9;
		else if(!timeUnit.compare("Ts"))
			iMultiplier = 1e-12;
		else						// seconds
			iMultiplier = 1.0;

		iMultiplier /= frequency.QuadPart;
	} // end StopWatch default constructor




				/*******************
				* global operators *
				*******************/

std::ostream &operator<<(std::ostream &outStream, StopWatch &timer)				 // operator <<
{
	outStream << std::setw(15) << timer.pop() << timer.getUnit() << " passed since last checkpoint." << std::endl;
	return outStream;
} // end function operator <<
