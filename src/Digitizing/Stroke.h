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

#ifndef STROKE_H
#define STROKE_H

// includes
#include "StrokePoint.h"
#include <Color/glColor.h>
#include <Graphics/glVertex2.h>
#include <vector>
#include <algorithm>
#include <algorithms.h>

template<typename StoredType = double , typename ColorType = double>
struct Stroke
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Stroke()																							// Stroke default constructor
	{
		// do nothing
	} // end Stroke default constructor


	inline Stroke(const Stroke &original)																	// Stroke copy constructor
		:land_point(original.land_point),lift_point(original.lift_point),
		curve(original.curve),color(original.color),width(original.width)
	{
		// empty body
	} // end Stroke copy constructor


	inline ~Stroke()																						// Stroke destructor
	{
		// empty body
	} // end Stroke destructor




	/************
	* operators *
	************/

	inline Stroke &operator = (const Stroke &original)														// operator =
	{
		land_point = original.land_point;
		lift_point = original.lift_point;
		curve = original.curve;
		color = original.color;
		width = original.width;
		return *this;
	} // end function operator =


	bool operator == (const Stroke &right) const															// operator ==
	{
		return land_point == right.land_point && lift_point == right.lift_point &&
			curve == right.curve && color == right.color && width == right.width;
	} // end function operator ==


	inline bool operator != (const Stroke &right) const														// operator !=
	{
		return !(*this == right);
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline Stroke &setLandPoint(const StrokePoint<StoredType> &point)										// setLandPoint
	{
		land_point = point;
		return *this;
	} // end function setLandPoint


	inline Stroke &setLiftPoint(const StrokePoint<StoredType> &point)										// setLiftPoint
	{
		lift_point = point;
		return *this;
	} // end function setLiftPoint


	inline Stroke &setCurve(const std::vector<StrokePoint<StoredType> > &points)							// setCurve
	{
		curve = points;
		return *this;
	} // end function setCurve


	inline Stroke &setColor(const RGBA::Color<ColorType> &strokeColor)										// setColor
	{
		color = strokeColor;
		return *this;
	} // end function setColor


	inline Stroke &setWidth(StoredType strokeWidth)															// setWidth
	{
		width = strokeWidth;
		return *this;
	} // end function setWidth


	inline Stroke &display()																				// display
	{
		static void (*const disambiguate)(const Vector2D<StoredType> &) = glVertex2;

		glLineWidth(width);
		glColor(color);
		glBegin(GL_LINE_STRIP);
			glVertex2(land_point);
			std::for_each(curve.begin(),curve.end(),disambiguate);
			glVertex2(lift_point);
		glEnd();
		//glPointSize(1.5*width);
		//glBegin(GL_POINTS);
		//	glVertex2(land_point);
		//	glVertex2(lift_point);
		//glEnd();
		return *this;
	} // end function display


	inline Stroke &display(StoredType zoom)																	// display
	{
		static void (*const disambiguate)(const Vector2D<StoredType> &) = glVertex2;

		glLineWidth(width*zoom);
		glColor(color);
		glBegin(GL_LINE_STRIP);
			glVertex2(land_point);
			std::for_each(curve.begin(),curve.end(),disambiguate);
			glVertex2(lift_point);
		glEnd();
		//glPointSize(1.5*width*zoom);
		//glBegin(GL_POINTS);
		//	glVertex2(land_point);
		//	glVertex2(lift_point);
		//glEnd();
		return *this;
	} // end function display


	inline Stroke &displayPoints()																			// displayPoints
	{
		static void (*const disambiguate)(const Vector2D<StoredType> &) = glVertex2;

		glPointSize(width);
		glColor(color);
		glBegin(GL_POINTS);
			std::for_each(curve.begin(),curve.end(),disambiguate);
		glBegin(GL_POINTS);
		glPointSize(2*width);
		glEnd();
			glVertex2(land_point);
			glVertex2(lift_point);
		glEnd();
		return *this;
	} // end function displayPoints


	inline Stroke &displayPoints(StoredType zoom)															// displayPoints
	{
		static void (*const disambiguate)(const Vector2D<StoredType> &) = glVertex2;

		glPointSize(width*zoom);
		glColor(color);
		glBegin(GL_POINTS);
			std::for_each(curve.begin(),curve.end(),disambiguate);
		glBegin(GL_POINTS);
		glPointSize(2*width*zoom);
		glEnd();
			glVertex2(land_point);
			glVertex2(lift_point);
		glEnd();
		return *this;
	} // end function displayPoints


	inline Stroke &move(const Vector2D<StoredType> &displacement)											// move
	{
		Vector2D<StoredType> &(*disambiguate)(Vector2D<StoredType> &,const Vector2D<StoredType> &) = operator+=;
		land_point += displacement;
		lift_point += displacement;
		apply(curve.begin(),curve.end(),disambiguate,displacement);
		return *this;
	} // end function move



	/***************
	* data members *
	***************/

	StrokePoint<StoredType> land_point;
	StrokePoint<StoredType> lift_point;
	std::vector<StrokePoint<StoredType> > curve;
	RGBA::Color<ColorType> color;
	StoredType width;

}; // end class Stroke

#endif // STROKE_H