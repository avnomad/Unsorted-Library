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

#ifndef SQUAREGRID_H
#define SQUAREGRID_H

#include <cmath>
#include "DisplayList.h"

template<typename FloatingPointType = double>
class SquareGrid : public DisplayList
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline SquareGrid()																		// SquareGrid default constructor
	{
		// do nothing (the object must be initialized later by the compile mehtod).
	} // end SquareGrid default constructor


	inline SquareGrid(unsigned int n)														// SquareGrid constructor
	{
		compile(n); // create a square grid of nxn cells in the square [0,1]x[0,1].
	} // end SquareGrid constructor


	inline SquareGrid(FloatingPointType smallSide , FloatingPointType largeSide)			// SquareGrid constructor
	{
		compile(smallSide,largeSide);	// create a square grid with halfside s = smallSide*ceil(largeSide/2/smallSide)
										// in the square [-s,s]x[-s,s] with cell of side smallSide.
	} // end SquareGrid constructor


	/************
	* operators *
	************/


	/*******************
	* member functions *
	*******************/

	SquareGrid &compile(unsigned int n)														// compile
	{
		FloatingPointType step = 1.0/n;
		FloatingPointType coord = 1;

		glNewList(iList,GL_COMPILE);
			glBegin(GL_LINES);
				glVertex2d(0,0);	// vertical
				glVertex2d(0,1);
				glVertex2d(0,0);	// horizontal
				glVertex2d(1,0);
				while(n--)
				{
					glVertex2d(coord,0);	// vertical
					glVertex2d(coord,1);
					glVertex2d(0,coord);	// horizontal
					glVertex2d(1,coord);
					coord -= step;
				} // end while				
			glEnd();
		glEndList();
		return *this;
	} // end function compile

	SquareGrid &compile(FloatingPointType smallSide , FloatingPointType largeSide)			// compile
	{
		unsigned int n = std::ceil(largeSide/2/smallSide);
		FloatingPointType coord = largeSide = n*smallSide;

		glNewList(iList,GL_COMPILE);
			glBegin(GL_LINES);
				glVertex2d(0,-largeSide);	// vertical
				glVertex2d(0,largeSide);
				glVertex2d(-largeSide,0);	// horizontal
				glVertex2d(largeSide,0);
				while(n--)
				{
					glVertex2d(coord,-largeSide);	// vertical
					glVertex2d(coord,largeSide);
					glVertex2d(-coord,-largeSide);	// vertical
					glVertex2d(-coord,largeSide);
					glVertex2d(-largeSide,coord);	// horizontal
					glVertex2d(largeSide,coord);
					glVertex2d(-largeSide,-coord);	// horizontal
					glVertex2d(largeSide,-coord);
					coord -= smallSide;
				} // end while				
			glEnd();
		glEndList();
		return *this;
	} // end function compile

private:

	/***************
	* data members *
	***************/

	// only the inherited

}; // end class SquareGrid

#endif // SQUAREGRID_H
