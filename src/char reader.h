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