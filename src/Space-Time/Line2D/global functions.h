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

template<typename StoredType>
inline bool perpendicular(const Line2D<StoredType> &line1 , const Line2D<StoredType> &line2 , StoredType accuracy = 1e-6)// perpendicular
{
	return fabs(line1.getA()*line2.getA() + line1.getB()*line2.getB()) < accuracy;
} // end function perpendicular


template<typename StoredType>
inline bool parallel(const Line2D<StoredType> &line1 , const Line2D<StoredType> &line2 , StoredType accuracy = 1e-6)	// parallel
{
	return fabs(line1.getA()*line2.getB() - line2.getA()*line1.getB()) < accuracy;
} // end function parallel


template<typename StoredType>
inline Vector2D<StoredType> intersection(const Line2D<StoredType> &line1 , const Line2D<StoredType> &line2)				// intersection
{
	Vector2D<StoredType> temp;
	StoredType D = line1.getA()*line2.getB() - line2.getA()*line1.getB();
#ifdef DEBUG
	if(D == 0) throw LogicError("A ZeroDeterminant","ASL","Line2D::intersection",
		"Unable to compute the intersection of the given lines because the lines are parallel.");
#endif
	temp.x = (line1.getB()*line2.getC() - line2.getB()*line1.getC()) / D;
	temp.y = (line2.getA()*line1.getC() - line1.getA()*line2.getC()) / D;
	return temp;
} // end function intersection


template<typename StoredType>
inline StoredType distance(const Vector2D<StoredType> &point , const Line2D<StoredType> &line)							// distance
{
	StoredType temp = sqrt(line.getA()*line.getA() + line.getB()*line.getB());
#ifdef DEBUG
	if(temp == 0) throw LogicError("An InconsistentLineObject","ASL","Line2D::distance",
		"The supplied line object was not in a consistent state (it was A=B=0).");
#endif
	return fabs(line.getA()*point.x + line.getB()*point.y + line.getC()) / temp;			
} // end function distance

	/*
	 * this should be 1 multiplication cheaper that finding a point in
	 * line2 and then the distance between the point and line1.
	 */
template<typename StoredType>
inline StoredType distance(const Line2D<StoredType> &line1 , const Line2D<StoredType> &line2)							// distance
{
	StoredType temp = sqrt(line1.getA()*line1.getA() + line1.getB()*line1.getB());
#ifdef DEBUG
	if(temp == 0) throw LogicError("An InconsistentLineObject","ASL","Line2D::distance",
		"The first line object supplied was not in a consistent state (it was A=B=0).");
	if(!parallel(line1,line2)) throw LogicError("A NotParallel","ASL","Line2D::distance",
		"Unable to compute the distance between the given lines because the lines are not parallel.");
#endif
	StoredType multiplier;
	if(fabs(line2.getA()) > fabs(line2.getB()))
		multiplier = line1.getA() / line2.getA();
	else
		multiplier = line1.getB() / line2.getB();
#ifdef DEBUG
	StoredType dummy = 0;
	if(multiplier == 1/dummy) throw LogicError("An InconsistentLineObject","ASL","Line2D::distance",
		"The second line object supplied was not in a consistent state (it was A=B=0).");
#endif
	return fabs(line1.getC() - multiplier*line2.getC()) / temp;			
} // end function distance

	/*
	 * 1 division cheaper and 1 addition more expensive than finding the perpendicular
	 * line and it's intersection wiht the given line, or equivalently evaluating the
	 * "simplified" formula produced this way.
	 */
template<typename StoredType>
inline Vector2D<StoredType> projection(const Vector2D<StoredType> &point , const Line2D<StoredType> &line)				// projection
{
	StoredType temp = line.getA()*line.getA() + line.getB()*line.getB();
#ifdef DEBUG
	if(temp == 0) throw LogicError("An InconsistentLineObject","ASL","Line2D::projection",
		"The supplied line object was not in a consistent state (it was A=B=0).");
#endif
	StoredType multiplier = (line.getA()*point.x + line.getB()*point.y + line.getC()) / temp;

	return Vector2D<StoredType>(point.x - multiplier*line.getA() , point.y - multiplier*line.getB());
} // end function projection


template<typename StoredType>
inline StoredType operator ^ (const Line2D<StoredType> &line1 , const Line2D<StoredType> &line2)						// operator ^
{
	Vector2D<StoredType> v1 = line1.direction();
#ifdef DEBUG
	if(v1 == Vector2D<StoredType>(0,0)) throw LogicError("An InconsistentLineObject","ASL","Line2D::operator ^",
		"The first line object supplied was not in a consistent state (it was A=B=0).");
#endif
	Vector2D<StoredType> v2 = line2.direction();
#ifdef DEBUG
	if(v2 == Vector2D<StoredType>(0,0)) throw LogicError("An InconsistentLineObject","ASL","Line2D::operator ^",
		"The second line object supplied was not in a consistent state (it was A=B=0).");
#endif
	return std::acos((v1*v2) / (v1.norm()*v2.norm()));
} // end function operator ^


template<typename StoredType>
inline bool vertical(const Line2D<StoredType> &line)																	// vertical
{
	return line.getB() == 0;
} // end function vertical


template<typename StoredType>
inline bool horizontal(const Line2D<StoredType> &line)																	// horizontal
{
	return line.getA() == 0;
} // end function horizontal


template<typename StoredType>	// creates the line x == x0
inline Line2D<StoredType> vertical(StoredType x0)																		// vertical
{
	return Line2D<StoredType>(1,0,-x0);
} // end function vertical


template<typename StoredType>	// creates the line y == y0
inline Line2D<StoredType> horizontal(StoredType y0)																		// horizontal
{
	return Line2D<StoredType>(0,1,-y0);
} // end function horizontal


template<typename StoredType>
inline bool closerToVertical(const Line2D<StoredType> &line)															// closerToVertical
{
	return fabs(line.getA()) > fabs(line.getB());
} // end function closerToVertical


template<typename StoredType>
inline bool closerToHorizontal(const Line2D<StoredType> &line)															// closerToHorizontal
{
	return fabs(line.getA()) < fabs(line.getB());
} // end function closerToHorizontal
