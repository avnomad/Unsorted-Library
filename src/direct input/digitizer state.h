#ifndef DIGITIZER_STATE_H
#define DIGITIZER_STATE_H

#include <iostream>
#include <iomanip>
#include <windows/common.h>

struct DigitizerState
{
					/**************************
					* contructors & destructor*
					**************************/
	
	DigitizerState()																							// default constructor
		:Xaxis(0),Yaxis(0),TipPressure(0),Xtilt(0),Ytilt(0),Azimuth(0),Altitude(0),Twist(0),
		Eraser(0),Invert(0),BarrelSwitch(0),TipSwitch(0),InRange(0)
	{
		// empty body
	} // end DigitizerState default constructor

	DigitizerState(const DigitizerState &original)																// copy constructor
		:Xaxis(original.Xaxis),Yaxis(original.Yaxis),TipPressure(original.TipPressure),Xtilt(original.Xtilt),Ytilt(original.Ytilt),
		Azimuth(original.Azimuth),Altitude(original.Altitude),Twist(original.Twist),
		Eraser(original.Eraser),Invert(original.Invert),BarrelSwitch(original.BarrelSwitch),TipSwitch(original.TipSwitch),InRange(original.InRange)
	{
		// empty body
	} // end DigitizerState copy constructor


						/************
						* operators *
						************/

	DigitizerState &operator=(const DigitizerState &original)													// operator =
	{
		Xaxis = original.Xaxis;
		Yaxis = original.Yaxis;
		TipPressure = original.TipPressure;
		Xtilt = original.Xtilt;
		Ytilt = original.Ytilt;
		Azimuth = original.Azimuth;
		Altitude = original.Altitude;
		Twist = original.Twist;
		Eraser = original.Eraser;
		Invert = original.Invert;
		BarrelSwitch = original.BarrelSwitch;
		TipSwitch = original.TipSwitch;
		InRange = original.InRange;

		return *this;
	} // end function operator =

	bool operator==(const DigitizerState &right) const															// operator ==
	{
		return Xaxis == right.Xaxis && Yaxis == right.Yaxis && TipPressure == right.TipPressure &&
			Xtilt == right.Xtilt && Ytilt == right.Ytilt && Azimuth == right.Azimuth && Altitude == right.Altitude &&
			Twist == right.Twist &&	Eraser == right.Eraser && Invert == right.Invert &&
			BarrelSwitch == right.BarrelSwitch && TipSwitch == right.TipSwitch && InRange == right.InRange;
	} // end function operator ==

	inline bool operator!=(const DigitizerState &right) const													// operator !=
	{
		return !(*this == right);
	} // end function operator !=


					/*******************
					* member functions *
					*******************/


	/***************
	* data members *
	***************/
	
	LONG Xaxis;
	LONG Yaxis;
	LONG TipPressure;
	LONG Xtilt;
	LONG Ytilt;
	LONG Azimuth;
	LONG Altitude;
	LONG Twist;
	BYTE Eraser;
	BYTE Invert;
	BYTE BarrelSwitch;
	BYTE TipSwitch;
	BYTE InRange;
	BYTE padding[3];
}; // end struct DigitizerState


std::ostream &operator<<(std::ostream &outStream , const DigitizerState &state)										// operator <<
{
	outStream << std::left << std::setw(12) << "X axis" << std::right << std::setw(15) << state.Xaxis << '\n';
	outStream << std::left << std::setw(12) << "Y axis" << std::right << std::setw(15) << state.Yaxis << '\n';
	outStream << std::left << std::setw(12) << "Tip Pressure" << std::right << std::setw(15) << state.TipPressure << '\n';
	outStream << std::left << std::setw(12) << "X tilt" << std::right << std::setw(15) << state.Xtilt << '\n';
	outStream << std::left << std::setw(12) << "Y tilt" << std::right << std::setw(15) << state.Ytilt << '\n';
	outStream << std::left << std::setw(12) << "Azimuth" << std::right << std::setw(15) << state.Azimuth << '\n';
	outStream << std::left << std::setw(12) << "Altitude" << std::right << std::setw(15) << state.Altitude << '\n';
	outStream << std::left << std::setw(12) << "Twist" << std::right << std::setw(15) << state.Twist << '\n';
	outStream << std::left << std::setw(12) << "Eraser" << std::right << std::setw(15) << ((state.Eraser & 0x80) ? "pressed" : "released") << '\n';
	outStream << std::left << std::setw(12) << "Invert" << std::right << std::setw(15) << ((state.Invert & 0x80) ? "pressed" : "released") << '\n';
	outStream << std::left << std::setw(12) << "BarrelSwitch" << std::right << std::setw(15) << ((state.BarrelSwitch & 0x80) ? "pressed" : "released") << '\n';
	outStream << std::left << std::setw(12) << "TipSwitch" << std::right << std::setw(15) << ((state.TipSwitch & 0x80) ? "pressed" : "released") << '\n';
	outStream << std::left << std::setw(12) << "InRange" << std::right << std::setw(15) << ((state.InRange & 0x80) ? "pressed" : "released") << endl;

	return outStream;
} // end function operator <<


#endif // DIGITIZER_STATE_H