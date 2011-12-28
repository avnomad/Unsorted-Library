#ifndef LINE2D_H
#define LINE2D_H

// compilation control #defines:
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef DEBUG
#include <exceptions/exceptions.h>
#endif


#include <cmath>
#include <Space-Time/Vector2D.h>
#include <Utility.h>

template<typename StoredType = double>
class Line2D	// line represented as Ax + By + C == 0
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Line2D()																						// Line2D default constructor
	{
		// do nothing
	} // end Line2D default constructor


	inline Line2D(const Line2D &original)																// Line2D copy constructor
		:iA(original.iA),iB(original.iB),iC(original.iC)
	{
		// empty body
	} // end Line2D copy constructor


	inline Line2D(StoredType A,StoredType B,StoredType C)												// Line2D constructor
		:iA(A),iB(B),iC(C)
	{
		// empty body
	} // end Line2D constructor

	inline Line2D(const Vector2D<StoredType> &direction , const Vector2D<StoredType> &point)			// Line2D constructor
	{
		setTo(direction,point);
	} // end Line2D constructor


	template<typename IIter>
	inline Line2D(IIter begin , IIter end)																// Line2D constructor
	{
		setTo(begin,end);
	} // end Line2D constructor


	template<typename ContType>
	inline Line2D(ContType container)																	// Line2D constructor
	{
		setTo(container);
	} // end Line2D constructor


	inline ~Line2D()																					// Line2D destructor
	{
		// empty body
	} // end Line2D destructor




	/************
	* operators *
	************/

	inline Line2D &operator = (const Line2D &original)													// operator =
	{
		iA = original.iA;
		iB = original.iB;
		iC = original.iC;
		return *this;
	} // end function operator =


	inline bool operator == (const Line2D &right) const													// operator ==
	{
		return iA == right.iA && iB == right.iB && iC == right.iC;
	} // end function operator ==


	inline bool operator != (const Line2D &right) const													// operator !=
	{
		return !(*this == right);
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

#include "Line2D/setters and getters.h"

	inline Vector2D<StoredType> direction() const														// direction
	{
		return Vector2D<StoredType>(-iB,iA);
	} // end function direction


	inline Vector2D<StoredType> perpendicular() const													// perpendicular
	{
		return Vector2D<StoredType>(iA,iB);
	} // end function perpendicular


	inline Line2D &setTo(const Vector2D<StoredType> &direction , const Vector2D<StoredType> &point)		// setTo
	{
		iA = direction.y;
		iB = -direction.x;
		iC = direction.x*point.y - direction.y*point.x;
		return *this;
	} // end function setTo


	/****************************************************************************************************
	*																									*
	*		This is an implementation of the Total Least Squares method for finding the "best"			*
	*		line that passes throw a sequence of points. We assume that the input iterators				*
	*		begin and end point to the start and just after the end respectively of a sequence of		*
	*		objects that have public x and y members which are interpreted as the coordenants of		*
	*		the points in question. There exist some sets of points that give an infinite number		*
	*		of "best" lines when the "best" line is defined as the line l for which Ó(d(pi,l)^2)		*
	*		is minimum. In these cases the line which minimizes Ó(yi-b-axi)^2 is selected instead.		*
	*		First we compute the sum of all x's, y's, x^2's, y^2's, x*y's and the number of points		*
	*		n. We have to compute this too because the iterators may not be subtractable and may		*
	*		not point to the ends of a container (to use the size method). Then we calculate a			*
	*		matrix | a  c | and it's eigenvalues and last we find the eigenvector corresponding to		*
	*		the	   | c  b | eigenvalue with the least absolute value. The line is perpendicular to		*
	*		that vector and passes from the point (average X , average Y).								*
	*																									*
	****************************************************************************************************/

	template<typename IIter>
	Vector2D<StoredType> setTo(IIter begin , IIter end)													// setTo
	{
		// Some space could be saved if I reused variables but I leave that to the optimizer!
		StoredType sx,sy,sx2,sy2,sxy,avgX,avgY;	// s for sum.
		unsigned int n = 0;
		StoredType a,b,c,l1,l2;
		StoredType x,y;

		// calculate the sums.
		sx = sy = sx2 = sy2 = sxy = 0;
		while(begin != end)	// while there is another point
		{
			x = begin->x;	// cache x and y. this might be usefull if operator -> is expensive.
			y = begin->y;	// Hopefully the optimizer will take care of it if not.
			++begin;	// advance to the next point.
			sx += x;
			sy += y;
			sx2 += x*x;
			sy2 += y*y;
			sxy += x*y;
			++n;
		} // end while

		//if(n < 2) return Vector2D<StoredType>(sx,sy);	// you can't get a line with less than 2 points.

		// calculate the averages
		avgX = sx / n;
		avgY = sy / n;

		// calculate the matrix
		a = sx2 - avgX*sx;
		b = sy2 - avgY*sy;
		c = sxy - avgX*sy;

		if(a == b && c == 0)	// if there are infinite "best" lines
		{
			if(a == 0) throw LogicError("An AllPointsTheSame","ASL","Line2D::setTo",
				"It appears that all the points in the sequence have the same coordinants and thus, no line can be drawn.");
			iA = 0;	// n*sxy - sx*sy == n*c == 0 at this point of execution.
			iB = -a*n; // sx*sx - n*sx2 == -n*a at this point of execution.
			iC = -avgY*iB;	// sy*sx2 - sx*sxy == -avgY*iB at this point of execution.
		}
		else	// if there is a single "best" line
		{
			// calculate the eigenvalues
			x = a - b;	// intermediate
			y = sqrt(x*x + 4*c*c);	// discriminant
			x = a + b;	// intermediate
			l1 = (x + y) / 2;	// first eigenvalue
			l2 = (x - y) / 2;	// second eigenvalue
			if(fabs(l1) < fabs(l2))
			{
				a -= l1;
				b -= l1;
			}
			else
			{
				a -= l2;
				b -= l2;
			} // end else
			
			// calculate the eigenvector
			if(fabs(a) > fabs(b))	// find a nonzero vector
			{
				iA = -c;
				iB = a;
			}
			else
			{
				iA = -b;
				iB = c;
			} // end else
			
			iC = -(iA*avgX + iB*avgY);
		} // end else (single line)	
		return Vector2D<StoredType>(avgX,avgY);
	} // end function setTo


	template<typename ContType>
	inline Vector2D<StoredType> setTo(ContType container)												// setTo
	{
		return setTo(container.begin(),container.end());	// could have made a faster implementation
			// by spliting the setTo(iter,iter) (to reuse the common code) and avoiding the ++n.
	} // end function setTo


	inline Line2D parallel(const Vector2D<StoredType> &point) const										// parallel
	{
		return Line2D(direction(),point);
	} // end function parallel


	inline Line2D perpendicular(const Vector2D<StoredType> &point) const								// perpendicular
	{
		return Line2D(perpendicular(),point);
	} // end function perpendicular


	inline StoredType getX(StoredType y) const															// getX
	{
#ifdef DEBUG
		if(iA == 0) throw RuntimeError("A InvalidMapping","ASL","Line2D::getX",
			"An infinite or zero number of x's correspond to a given y. (the line is horizontal).");
#endif
		return - (iB*y + iC) / iA;
	} // end function getX


	inline StoredType getY(StoredType x) const															// getY
	{
#ifdef DEBUG
		if(iB == 0) throw RuntimeError("A InvalidMapping","ASL","Line2D::getY",
			"An infinite or zero number of y's correspond to a given x. (the line is vetrical).");
#endif
		return - (iA*x + iC) / iB;
	} // end function getY


	inline Line2D &roundAngle(StoredType step , const Vector2D<StoredType> &center)						// roundAngle
	{
		StoredType angle = round(perpendicular().angle(),step);	// the new angle is the rounded old
		iA = cos(angle);	// calculate the new perpendicular vector
		iB = sin(angle);	// it will have unit lenght
		iC = -(iA*center.x + iB*center.y);	// the new line will pass from center.
		return *this;
	} // end function roundAngle


	inline Line2D &roundAngle(StoredType step , StoredType shift , const Vector2D<StoredType> &center)	// roundAngle
	{
		StoredType angle = round(perpendicular().angle()+shift,step) - shift;	// the new angle is the rounded old
		iA = cos(angle);	// calculate the new perpendicular vector
		iB = sin(angle);	// it will have unit lenght
		iC = -(iA*center.x + iB*center.y);	// the new line will pass from center.
		return *this;
	} // end function roundAngle


	inline Line2D &roundC(StoredType step)																// roundC
	{
		iC = round(iC,step*sqrt(iA*iA+iB*iB));
		return *this;
	} // end function roundC


	inline Line2D &roundC(StoredType step , const Vector2D<StoredType> &shift)							// roundC
	{
		StoredType C = iA*shift.x+iB*shift.y;
		iC = round(iC-C,step*sqrt(iA*iA+iB*iB)) + C;
		return *this;
	} // end function roundC



private:

	/***************
	* data members *
	***************/

	StoredType iA;
	StoredType iB;
	StoredType iC;
}; // end class Line2D

#include "Line2D/global functions.h"

#endif // LINE2D_H