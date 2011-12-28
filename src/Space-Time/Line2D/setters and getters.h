
	/* setters */

inline Line2D &setA(StoredType A)												// setA
{
	iA = A;
	return *this;
} // end function setA


inline Line2D &setB(StoredType B)												// setB
{
	iB = B;
	return *this;
} // end function setB


inline Line2D &setC(StoredType C)												// setC
{
	iC = C;
	return *this;
} // end function setC


inline Line2D &setABC(StoredType A,StoredType B,StoredType C)					// setABC
{
	iA = A;
	iB = B;
	iC = C;
	return *this;
} // end function setABC



	/* getters */

inline StoredType getA() const													// getA
{
	return iA;
} // end function getA


inline StoredType getB() const													// getB
{
	return iB;
} // end function getB


inline StoredType getC() const													// getC
{
	return iC;
} // end function getC
