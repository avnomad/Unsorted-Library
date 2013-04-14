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

struct Unit
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Unit()																// Unit default constructor
		:name("ms")									// the default unit is milliseconds
	{
		LARGE_INTEGER clockFrequency;				// 64 bit integer.
		QueryPerformanceFrequency(&clockFrequency);	// get the frequency of the used clock.

		multiplier = 1e3 / clockFrequency.QuadPart;	// set multiplier to the number of milliseconds per clock tick.
	} // end Unit default constructor


	/************
	* operators *
	************/

	/*******************
	* member functions *
	*******************/



	/***************
	* data members *
	***************/

	std::string name;
	FloatingPointType multiplier;

}; // end class Unit