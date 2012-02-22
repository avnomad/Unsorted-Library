#ifndef TABLE_PAINTER_H
#define TABLE_PAINTER_H

#include <gl/glut.h>
#include <color.h>

template<typename StoredType , typename ColorType = double>
struct TablePainter
{
	// typedefs
	typedef StoredType stored_type;
	typedef RGBA::Color<ColorType> color_type;

	/***************************
	* contructors & destructor *
	***************************/

	inline TablePainter()																						// TablePainter default constructor
	{
		// do nothing
	} // end TablePainter default constructor


	inline TablePainter(const TablePainter &original)															// TablePainter copy constructor
		:trueColor(original.trueColor),falseColor(original.falseColor),
		gridColor(original.gridColor),columns(original.columns)
	{
		// empty body
	} // end TablePainter copy constructor


	inline TablePainter(color_type true_color,color_type false_color,color_type grid_color,unsigned int column)	// TablePainter constructor
		:trueColor(true_color),falseColor(false_color),
		gridColor(grid_color),columns(column)
	{
		// empty body
	} // end TablePainter conversion constructor


	inline ~TablePainter()																						// TablePainter destructor
	{
		// empty body
	} // end TablePainter destructor




	/************
	* operators *
	************/

	inline TablePainter &operator = (const TablePainter &original)												// operator =
	{
		trueColor = original.trueColor;
		falseColor = original.falseColor;
		gridColor = original.gridColor;
		columns = original.columns;
		return *this;
	} // end function operator =


	inline bool operator == (const TablePainter &right) const													// operator ==
	{
		return trueColor == right.trueColor && falseColor == right.falseColor &&
			gridColor == right.gridColor &&	columns == right.columns;
	} // end function operator ==


	inline bool operator != (const TablePainter &right) const													// operator !=
	{
		return trueColor != right.trueColor || falseColor != right.falseColor ||
			gridColor != right.gridColor ||	columns != right.columns;
	} // end function operator !=


	/*******************
	* member functions *
	*******************/

	inline TablePainter &setTrueColor(color_type true_color)													// setTrueColor
	{
		trueColor = true_color;
		return *this;
	} // end function setTrueColor


	inline TablePainter &setFalseColor(color_type false_color)													// setFalseColor
	{
		falseColor = false_color;
		return *this;
	} // end function setFalseColor


	inline TablePainter &setGridColor(color_type grid_color)													// setGridColor
	{
		gridColor = grid_color;
		return *this;
	} // end function setGridColor


	inline TablePainter &setColumns(unsigned int columns)															// setColumns
	{
		this->columns = columns;
		return *this;
	} // end function setColumns


	template<typename IIter>
	TablePainter &display(IIter begin , IIter end)
	{
		unsigned int c = columns;
		unsigned int rows = 0;
		int x = 0 , y = 0;

		while(begin != end)
		{
			if(*begin)
				glColor(trueColor);
			else
				glColor(falseColor);
			glRecti(x,y,x+10,y-10);
			x += 10;
			++begin;
			if(!--c)
			{
				y -= 10;
				x = 0;
				c = columns;
				++rows;
			} // end if
		} // end while

		if(x)
		{
			++rows;
			c = columns;
		} // end if

		glColor(gridColor);
		glBegin(GL_LINES);
			y = -10*rows;
			x = 0;
			glVertex2i(0,0);
			glVertex2i(0,y);
			while(c--)
			{
				x += 10;
				glVertex2i(x,0);
				glVertex2i(x,y);
			} // end while
			y = 0;
			glVertex2i(0,0);
			glVertex2i(x,0);
			while(rows--)
			{
				y -= 10;
				glVertex2i(0,y);
				glVertex2i(x,y);
			} // end while
		glEnd();
		return *this;
	} // end method display



	/***************
	* data members *
	***************/

	color_type trueColor;
	color_type falseColor;
	color_type gridColor;
	unsigned int columns;	
}; // end class TablePainter

#endif // TABLE_PAINTER_H