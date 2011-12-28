template<typename StoredType , typename ArgType>
inline Color<StoredType> operator * (ArgType left , const Color<StoredType> &right)						// operator * (scalar product)
{
	return Color<StoredType>(left*right.getRed() , left*right.getGreen() , left*right.getBlue() , right.getAlpha());
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Color<StoredType> operator * (const Color<StoredType> &left , ArgType right)						// operator * (scalar product)
{
	return Color<StoredType>(left.getRed()*right , left.getGreen()*right , left.getBlue()*right , left.getAlpha());
} // end function operator * (scalar product)


template<typename StoredType , typename ArgType>
inline Color<StoredType> operator / (const Color<StoredType> &left , ArgType right)						// operator / (division by scalar)
{
	return Color<StoredType>(left.getRed()/right , left.getGreen()/right , left.getBlue()/right , left.getAlpha());
} // end function operator / (division by scalar)


template<typename StoredType , typename ArgType>
inline Color<StoredType> &operator *= (Color<StoredType> &left , ArgType right)							// operator *=
{
	left.setRed(left.getRed() * right);
	left.setGreen(left.getGreen() * right);
	left.setBlue(left.getBlue() * right);
	return left;
} // end function operator *=


template<typename StoredType , typename ArgType>
inline Color<StoredType> &operator /= (Color<StoredType> &left , ArgType right)							// operator /=
{
	left.setRed(left.getRed() / right);
	left.setGreen(left.getGreen() / right);
	left.setBlue(left.getBlue() / right);
	return left;
} // end function operator /=
