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

#ifndef CHAR_READED_H
#define CHAR_READED_H

class CharReader //: public std::iterator<std::input_iterator_tag,char,ptrdiff_t,const char*,const char&>
{
public:
	typedef char value_type;
	typedef char &reference;
	typedef char *pointer;
	typedef std::input_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	inline CharReader() // default constructor
		:iFile(0),endReached(1)
	{
		// empty body.
	} // end CharReader default constructor

	inline CharReader(const CharReader &original) // copy constructor
		:readCharacter(original.readCharacter),iFile(original.iFile),endReached(original.endReached)
	{
		// empty body.
	} // end CharReader copy constructor

	inline CharReader(std::istream &inputFile)
		:readCharacter(inputFile?inputFile.get():0),iFile(&inputFile),endReached(!inputFile)
	{
		// empty body.
	} // end CharReader constructor

	inline const CharReader &operator++()
	{
		readCharacter = iFile->get();
		endReached = !*iFile;
		return *this;
	} // end function operator++

	inline CharReader operator++(int)
	{
		CharReader temp = *this;
		readCharacter = iFile->get();
		endReached = !*iFile;
		return temp;
	} // end function operator++

	inline char operator*()
	{
		return readCharacter;
	} // end function operator*

	inline const CharReader &operator=(const CharReader &original)
	{
		readCharacter = original.endReached;
		iFile = original.iFile;
		endReached = original.endReached;
		return *this;
	} // end function operator=

	inline bool operator==(const CharReader &other) const
	{
		return this->endReached == other.endReached;
	} // end function operator==

	inline bool operator!=(const CharReader &other) const
	{
		return this->endReached != other.endReached;
	} // end function operator!=

private:
	char readCharacter;
	std::istream *iFile;
	bool endReached;
}; // end class CharReader

#endif // CHAR_READED_H