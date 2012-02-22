#ifndef COLOR_H
#define COLOR_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include <exceptions/exceptions.h>
#endif

#include <climits>

namespace RGBA
{

namespace component
{
#include "color/complement.h"
#include "color/max.h"
#include "color/min.h"
#include "color/inRange.h"
}; // end namespace component


template<typename StoredType = double>
class Color
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Color()																					// Color default constructor
	{
		// do nothing
	} // end Color default constructor


	inline Color(const Color &original)																// Color copy constructor
	{
		setRed(original.getRed());
		setGreen(original.getGreen());
		setBlue(original.getBlue());
		setAlpha(original.getAlpha());
	} // end Color copy constructor


	inline Color(const StoredType components[4])													// Color conversion constructor
	{													// converts an array of 4 color components
		setRed(components[0]).setGreen(components[1]);	// to a color object with the same components.
		setBlue(components[2]).setAlpha(components[3]);
	} // end Color conversion constructor


	inline Color(StoredType red , StoredType green , StoredType blue , StoredType alpha)			// Color constructor
	{
		setRed(red).setGreen(green).setBlue(blue).setAlpha(alpha);
	} // end Color constructor


	inline Color(StoredType red , StoredType green , StoredType blue)								// Color constructor
	{
		setRed(red).setGreen(green).setBlue(blue).setAlpha(component::max(StoredType(0)));
	} // end Color constructor


	inline ~Color()																					// Color destructor
	{
		// empty body
	} // end Color destructor




	/************
	* operators *
	************/

	inline Color &operator = (const Color &original)													// operator =
	{
		setRed(original.getRed());
		setGreen(original.getGreen());
		setBlue(original.getBlue());
		setAlpha(original.getAlpha());
		return *this;
	} // end function operator =


	bool operator == (const Color &right) const															// operator ==
	{
		return iComponents[0] == right.iComponents[0] && iComponents[1] == right.iComponents[1]
			&& iComponents[2] == right.iComponents[2] && iComponents[3] == right.iComponents[3];
	} // end function operator ==


	inline bool operator != (const Color &right) const													// operator !=
	{
		return !(*this == right);
	} // end function operator !=


	inline operator const StoredType * () const															// operator StoredType *
	{
		return iComponents;
	} // end function operator StoredType *


	inline operator StoredType * ()																		// operator StoredType *
	{
		return iComponents;
	} // end function operator StoredType *



	/*******************
	* member functions *
	*******************/


	inline Color &setRed(StoredType red)																// setRed
	{
#ifdef DEBUG
		if(!component::inRange(red)) throw OutOfRange("A ColorOutOfRange","ASL","RGBA::Color::setRed",
			"The red color component passed to the function does not appear to be in the valid range.");
#endif
		iComponents[0] = red;
		return *this;
	} // end function setRed


	inline Color &setGreen(StoredType green)															// setGreen
	{
#ifdef DEBUG
		if(!component::inRange(green)) throw OutOfRange("A ColorOutOfRange","ASL","RGBA::Color::setGreen",
			"The green color component passed to the function does not appear to be in the valid range.");
#endif
		iComponents[1] = green;
		return *this;
	} // end function setGreen


	inline Color &setBlue(StoredType blue)																// setBlue
	{
#ifdef DEBUG
		if(!component::inRange(blue)) throw OutOfRange("A ColorOutOfRange","ASL","RGBA::Color::setBlue",
			"The blue color component passed to the function does not appear to be in the valid range.");
#endif
		iComponents[2] = blue;
		return *this;
	} // end function setBlue


	inline Color &setAlpha(StoredType alpha)															// setAlpha
	{
#ifdef DEBUG
		if(!component::inRange(alpha)) throw OutOfRange("A ColorOutOfRange","ASL","RGBA::Color::setAlpha",
			"The alpha color component passed to the function does not appear to be in the valid range.");
#endif
		iComponents[3] = alpha;
		return *this;
	} // end function setAlpha


	inline StoredType getRed() const																	// getRed
	{
		return iComponents[0];
	} // end function getRed


	inline StoredType getGreen() const																	// getGreen
	{
		return iComponents[1];
	} // end function getGreen


	inline StoredType getBlue() const																	// getBlue
	{
		return iComponents[2];
	} // end function getBlue


	inline StoredType getAlpha() const																	// getAlpha
	{
		return iComponents[3];
	} // end function getAlpha


	Color negative() const																				// negative
	{									// keeps the same alpha and inverts the color.
		using component::complement;
		return Color(complement(getRed()),complement(getGreen()),complement(getBlue()),getAlpha());
	} // end function negative

private:

	/***************
	* data members *
	***************/

	StoredType iComponents[4];

}; // end class Color

#include "Color/operators.h"

}; // end namespace RGBA

#endif // COLOR_H