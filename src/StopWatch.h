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