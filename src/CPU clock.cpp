#include "CPU clock.h"

CPUclock::Unit CPUclock::unit;


void CPUclock::setUnit(const std::string &timeUnit)										// setUnit
{									// does not change the values noted so far.
	LARGE_INTEGER clockFrequency;
	QueryPerformanceFrequency(&clockFrequency);

	if(!timeUnit.compare("ms"))			// fragments of second
		unit.multiplier = 1e3;
	else if(!timeUnit.compare("ìs"))
		unit.multiplier = 1e6;
	else if(!timeUnit.compare("ns"))
		unit.multiplier = 1e9;
	else if(!timeUnit.compare("ps"))
		unit.multiplier = 1e12;
	else if(!timeUnit.compare("ks"))	// multiples of second
		unit.multiplier = 1e-3;
	else if(!timeUnit.compare("Ms"))
		unit.multiplier = 1e-6;
	else if(!timeUnit.compare("Gs"))
		unit.multiplier = 1e-9;
	else if(!timeUnit.compare("Ts"))
		unit.multiplier = 1e-12;
	else								// seconds
		unit.multiplier = 1.0;

	unit.multiplier /= clockFrequency.QuadPart;
	unit.name = timeUnit;
} // end function setUnit
