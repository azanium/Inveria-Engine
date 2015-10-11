
#ifndef _DIMENSION_H_
#define _DIMENSION_H_

//! To keep anything hidden from the user, move the implementation into
//! the .CPP file, but i'm too lazy to do such things, so this class only
//! has one file Dimension.h. That's all it takes to use the Dimension. 

namespace inveria
{
namespace core
{

template <class T>
class Dimension
{
public:
	Dimension()
		: Width(0), Height(0) {};

	Dimension( T width, T height )
		: Width(width), Height(height) {};

	Dimension( const Dimension<T> &dimension )
		: Width(dimension.Width), Height(dimension.Height) {};

	bool operator ==( const Dimension<T> &dimension ) const
	{
		return (m_nWidth == dimension.Width) && (m_nHeight == dimension.Height);
	}
    
	bool operator !=( const Dimension<T> &dimension ) const
	{
		return (m_nWidth != dimension.Width) || (m_nHeight != dimension.Height);
	}

	const Dimension<T>& operator =( const Dimension<T> &dimension )
	{
		Width = dimension.Width;
		Height = dimension.Height;

		return *this;
	}

	T	Width, Height;
};

}	// namespace core
}	// namespace inveria

#endif	// _Dimension_H_
