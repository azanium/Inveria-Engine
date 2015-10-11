#ifndef _ICOLOR_H_
#define _ICOLOR_H_

#include "Types.h"

namespace inveria
{
namespace graphics
{

enum E_COLOR_FORMAT
{
	ECF_R5G6B5 = 0,		// no 16 bits texture color format supported yet..
	ECF_R8G8B8,
	ECF_A8R8G8B8
};

#define RGB16BIT(r, g, b)	(((r % 32) << 11) + ((g % 64) << 5) + (b % 32))
#define RGB16TO32BIT(color)	( (0xff < 24) | ((color >> 11 & 0x1F) << 16) | ((color >> 5 & 0x3F) << 8) | (color & 0x1F))

//! Enhanced version of color class, it used to be a struct: IColor, but now it is a class: IColor
class Color
{
public:

	inline Color( void ) { set( 255, 255, 255, 255 ); }

	inline Color( u32 r, u32 g, u32 b, u32 a = 255 ):
		   color( ((a & 0xff)  << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff) ) { }
	
	inline Color( u32 color ): color(color) {}

	inline void set( const Color &color ) { set(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()); }
	inline void set( u32 r, u32 g, u32 b, u32 a ) { color = ( ((a & 0xff)  << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)); }
    
	inline u32	getRed( void ) const { return (color>>16) & 0xff; }
	inline u32	getGreen( void ) const { return ((color>>8) & 0xff); }
	inline u32	getBlue( void ) const { return (color & 0xff); }
	inline u32	getAlpha( void ) const { return ((color>>24) & 0xff); }

	inline f32  getRedf( void ) const { return (f32)(getRed() / 255.f); }
	inline f32  getGreenf( void ) const { return (f32)(getGreen() / 255.f); }
	inline f32  getBluef( void ) const { return (f32)(getBlue() / 255.f); }
	inline f32  getAlphaf( void ) const { return (f32)(getAlpha() / 255.f); }

	inline void toRGBA( u8* dest ) const
	{
		*dest	= getRed();
		*++dest	= getGreen();
		*++dest = getBlue();
		*++dest	= getAlpha();
	};
		
	inline void setRed( u32 r ) { color = ((color>>24 & 0xff) << 24) | ((r & 0xff) << 16) | ((color>>8 & 0xff) << 8) | (color & 0xff); }
	inline void setGreen( u32 g ) { color = ((color>>24 & 0xff) << 24) | ((color>>16 & 0xff) << 16) | ((g & 0xff) << 8) | (color & 0xff); }
	inline void setBlue( u32 b ) { color = ((color>>24 & 0xff) << 24) | ((color>>16 & 0xff) << 16) | ((color>>8 & 0xff) << 8) | (b & 0xff); }
	inline void setAlpha( u32 a ) { color = ((a & 0xff) << 24) | ((color>>16 & 0xff) << 16) | ((color>>8 & 0xff) << 8) | (color & 0xff); }
	inline u32	getColor( void ) const { return color; }

	inline void	operator =( const Color &color ) { this->color = color.color; }
	inline bool operator ==( const Color &color ) const { return this->color == color.color; }
	inline bool operator !=( const Color &color ) const { return this->color != color.color; }

	u32 color;	
};

//! The color class for floating point value of RGBA
class Colorf
{
public:

	inline Colorf( void ): fR(0.0f), fG(0.0f), fB(0.0f), fA(0.0f) { }
	
	inline Colorf( f32 r, f32 g, f32 b, f32 a=1.0f ): fR(r), fG(g), fB(b), fA(a) { }
	//inline Colorf( u32 r, u32 g, u32 b, u32 a=255 ) { const f32 inv = 1.0f/255.0f; fR = r*inv; fG = g*inv; fB = b*inv; fA = a*inv; }

	inline Colorf( const Colorf &col ) { *this = col; }

	inline void SetF( f32 r, f32 g, f32 b, f32 a=1.0f ) { fR = r; fG = g; fB = b; fA = a; }
	inline void Set( u32 r, u32 g, u32 b, u32 a=255 ) { const f32 inv = 1.0f/255.0f; fR = r*inv; fG = g*inv; fB = b*inv; fA = a*inv; }

	inline void	SetRed( f32 r ) { fR = r; }
	inline void SetGreen( f32 g ) { fG = g; }
	inline void SetBlue( f32 b ) { fB = b; }
	inline void SetAlpha( f32 a ) { fA = a; }

	inline f32	GetRed( void ) const { return fR; }
	inline f32	GetGreen( void ) const { return fG; }
	inline f32	GetBlue( void ) const { return fB; }
	inline f32	GetAlpha( void ) const { return fA; }

	inline void	operator =( const Colorf &color ) 
	{ 
		fR = color.GetRed(); 
		fG = color.GetGreen(); 
		fB = color.GetBlue();
		fA = color.GetAlpha();
	};

	inline bool operator ==( const Colorf &color ) const
	{ 
		if ((fR == color.GetRed()) &&
			(fG == color.GetGreen()) &&
			(fB == color.GetBlue()) &&
			(fA == color.GetAlpha()))
			return true;

		return false;
	};

	inline bool operator !=( const Colorf &color )  const
	{ 
		if ((fR != color.GetRed()) ||
			(fG != color.GetGreen()) ||
			(fB != color.GetBlue()) ||
			(fA != color.GetAlpha()))
			return true;

		return false;
	};

	inline void Bias( void )
	{
		fR = fR * 0.5f + 0.5f;
		fG = fG * 0.5f + 0.5f;
		fB = fB * 0.5f + 0.5f;
		fA = fA * 0.5f + 0.5f;
	}

	f32	fR;
	f32 fG;
	f32 fB;
	f32 fA;
};

}	// namespace graphics
}	// namespace inveria

#endif	// _Color_H_
