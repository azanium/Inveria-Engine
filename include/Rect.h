#ifndef _RECT_H_
#define	_RECT_H_

#include "Types.h"

namespace inveria
{
namespace core
{

template <class T>
class Rect
{
public:
	T left, top, right, bottom;

	Rect( void ): left(0), top(0), right(0), bottom(0) { }
	Rect( T left, T top, T right, T bottom ): left(left), top(top), right(right), bottom(bottom) { }
	Rect( const Rect<T> &r ): left(r.left), top(r.top), right(r.right), bottom(r.bottom) { }

	void   clear( void )
	{
		left = top = right = bottom = 0;
	};

	inline bool operator ==( const Rect<T> &r ) const
	{
		if ((left == r.Left) && (top == r.Top) &&	(right == r.Right) && (bottom == r.Bottom))
			return true;

		return false;
	};

	inline bool operator !=( const Rect<T> &r ) const
	{
		if ((left != r.Left) || (top != r.Top) || (right != r.Right) || (bottom != r.Bottom))
			return true;

		return false;
	};

	inline void operator =( const Rect<T> &r )
	{
		left = r.Left; top = r.Top; right = r.Right; bottom = r.Bottom;
	};

};

typedef Rect<f32> Rectf;
typedef Rect<u32> Recti;
typedef Rect<l32> Rectl;

}	// namespace core
}	// namespace inveria

#endif	// _RECT_H_
