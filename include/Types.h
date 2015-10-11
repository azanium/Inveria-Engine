#ifndef _TYPES_H_
#define _TYPES_H_

#define PI			3.14159265f
#define PI2			1.5707963f
#define TWO_PI		6.2831853f
#define EPSILON		0.00001f

#define DEG_TO_RAD(x)	(x * PI / 180.0f)
#define RAD_TO_DEG(x)	(x * 180.0f / PI)
#define DEG2RAD			( 0.017453292f )

#ifndef NULL
#define NULL 0
#endif

#ifndef FRAND
#define FRAND(x) ((rand() / (float)RAND_MAX) * x)
#endif

// Platform Independent Variable Types
typedef	char			c8;

typedef signed char		s8;
typedef unsigned char	u8;

typedef signed short	s16;
typedef unsigned short	u16;

typedef int				i32;
typedef	int				s32;
typedef unsigned int	u32;

typedef	long			l32;
typedef unsigned long	ul32;

#ifdef _MSC_VER
	typedef _int64			i64;
	typedef signed _int64	s64;
	typedef unsigned _int64	u64;
#else
	typedef long long		s64;
	typedef unsigned long long u64;
#endif

typedef float			f32;
typedef double			f64;

static const s8			s8_min = s8(-128);
static const s8			s8_max = s8(127);

static const u8			u8_min = u8(0);
static const u8			u8_max = u8(255);

static const s16		s16_min = s16(-32768);
static const s16		s16_max = s16(32767);

static const u16		u16_min = u16(0);
static const u16		u16_max = s16(65535);

static const s32		s32_min = s32(-2147483647 - 1);
static const s32		s32_max = s32(2147483647);

static const u32		u32_min = u32(0);
static const u32		u32_max = u32(0xffffffff);

#ifndef MAXINT
#define MAXINT ( ( int ) (((( unsigned int )( -1 ) ) << 1 ) >> 1 ) )
#endif

#define BIT(x)			(1 << (x))

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if (p) { delete p; p = NULL; }; }
#endif

#ifndef SAFE_DELETE_A
#define SAFE_DELETE_A(p) {if (p) { delete [] p; p = NULL; }; }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); p = NULL; }; }
#endif

#if defined(WIN32) || defined(_MSC_VER)
#define DEBUG_BREAK( condition )	if (condition) { _asm int 3 }
#else
#define DEBUG_BREAK( condition )
#endif

#ifndef MAX_ID
#define MAX_ID	65535
#endif

inline f32 Rad2Deg( f32 fRad )
{
	const f32 k = 180.0f / PI;
	return fRad * k;
}

inline f32 Wrapf( f32 x, f32 min, f32 max)
{
	return (x < min)? (x - min) + max : (x > max)? (x - max) + min : x;

}

inline void Swapf( f32& a, f32& b )
{
	f32 c = a;
	a = b;
	b = c;
}

inline float Clampf( f32 x, f32 min, f32 max )
{
	return (x < min)? min : (x > max)? max : x;
}

#endif	// _TYPES_H_
