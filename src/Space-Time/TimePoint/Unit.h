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