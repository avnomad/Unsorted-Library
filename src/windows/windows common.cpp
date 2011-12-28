#include "common.h"
#include <iomanip>
using std::setw;

typedef unsigned int ui;

std::ostream &operator<<(std::ostream &outStream , const GUID &guid)
{
	std::ios_base::fmtflags flags = outStream.flags();	// store the old output format.
	char fill = outStream.fill('0');

	outStream << std::right << std::uppercase << std::hex <<	// set the new output format.
		setw(8) << guid.Data1 <<'-'<< setw(4) << guid.Data2 <<'-'<< 
		setw(4) << guid.Data3 <<'-'<< setw(2) << (ui)guid.Data4[0] << setw(2) << (ui)guid.Data4[1] <<'-'<<
		setw(2) << (ui)guid.Data4[2] << setw(2) << (ui)guid.Data4[3] << setw(2) << (ui)guid.Data4[4] <<
		setw(2) << (ui)guid.Data4[5] << setw(2) << (ui)guid.Data4[6] << setw(2) << (ui)guid.Data4[7];

	outStream.fill(fill);	// restore the old output format.
	outStream.flags(flags);
	return outStream;
} // end function operator <<
