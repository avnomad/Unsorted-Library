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

#ifndef STOPWATCH_H
#define STOPWATCH_H

// includes
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <windows.h>
#undef max
#undef min

class StopWatch
{
public:

				/**************
				* contructors *
				**************/

	// recognized units: Ts,Gs,Ms,ks,s,ms,ìs,ns,ps
	StopWatch(const std::string &timeUnit = "ìs");								// default constructor

	inline StopWatch::StopWatch(const StopWatch &original)						// copy constructor
		:iMultiplier(original.iMultiplier),iUnit(original.iUnit),iTimes(original.iTimes)
	{
		// empty body
	} // end StopWatch copy constructor


				/************
				* operators *
				************/


			/*******************
			* member functions *
			*******************/

	inline std::string StopWatch::getUnit() const								// getUnit
	{
		return iUnit;
	} // end function getUnit

	inline StopWatch &StopWatch::push()											// push
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		iTimes.push(currentTime.QuadPart * iMultiplier);
		return *this;
	} // end function push

	inline double StopWatch::pop()												// pop
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		double temp = currentTime.QuadPart*iMultiplier - iTimes.top();
		iTimes.pop();
		return temp;
	} // end function pop

	inline double StopWatch::peek()												// peek
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		return currentTime.QuadPart*iMultiplier - iTimes.top();
	} // end function peek

private:

		/***************
		* data members *
		***************/

	double iMultiplier;
	std::string iUnit;
	std::stack<double> iTimes;
}; // end class StopWatch



				/*******************
				* global operators *
				*******************/

std::ostream &operator<<(std::ostream &outStream, StopWatch &timer);			// operator <<

#endif // STOPWATCH_H