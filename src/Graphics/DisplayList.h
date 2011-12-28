#ifndef DISPLAYLIST_H
#define DISPLAYLIST_H

#include <gl/glut.h>

class DisplayList
{
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline DisplayList()															// DisplayList default constructor
		:iList(glGenLists(1))
	{
		// empty body
	} // end DisplayList default constructor


	explicit inline DisplayList(GLuint list)										// DisplayList conversion constructor
		:iList(list)
	{
		// empty body
	} // end DisplayList constructor


	inline ~DisplayList()															// DisplayList destructor
	{
		glDeleteLists(iList,1);
	} // end DisplayList destructor



	/************
	* operators *
	************/



	inline bool operator == (const DisplayList &right) const						// operator ==
	{
		return this->iList == right.iList;
	} // end function operator ==


	inline bool operator != (const DisplayList &right) const						// operator !=
	{
		return this->iList != right.iList;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline const DisplayList &call() const											// call
	{
		glCallList(iList);
		return *this;
	} // end function call

protected:

	/***************
	* data members *
	***************/

	GLuint iList;

private:
	inline DisplayList(const DisplayList &){}	// objects of this class should not be copied
	inline DisplayList &operator = (const DisplayList &){}
}; // end class DisplayList

#endif // DISPLAYLIST_H