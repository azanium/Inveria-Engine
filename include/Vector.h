#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Types.h"

namespace inveria
{
namespace core
{

//! This vector is seldom to use, but maybe i need this one day
template <class T>
class Vector4
{
public:
	T x, y, z, w;

	Vector4() 
	{ x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
	
	Vector4( T _x, T _y, T _z )
	{ x = _x; y = _y; z = _z; w = 1.0f; }

	inline void Set( T _x, T _y, T _z, T _w = 1.0f )
	{ x = _x; y = _y; z = _z; w = _w; }

	inline T	GetLength( void ) 
	{ 
		return (T) sqrt( x*x + y*y + z*z ); 
	}

	inline T	GetSqrLength( void )
	{ 
		return ( x*x + y*y + z*z); 
	}

	inline void Cross( const Vector4<T> &v1, const Vector4<T> &v2 )
	{ 
		x = v1.y*v2.z - v1.z*v2.y;
		y = v1.z*v2.x - v1.x*v2.z;
		z = v1.x*v2.y - v1.y*v2.x; 
	}

	inline void Normalize( void )
	{
		T f = (T)sqrt(x*x + y*y + z*z);
		x /= f; y /= f; z /= f;
	}

	inline T	AngleWith( Vector4<T> &v )
	{ 
		return (T) acos( ((*this)*v) / (this->GetLength()*v.GetLength()) ); 
	}

	inline void Sub( const Vector4<T> &v1, const Vector4<T> &v2 )
	{
		x = v2.x - v1.x;
		y = v2.y - v1.y;
		z = v2.z - v1.z;
		w = 1.0f;
	}

	void operator +=( const Vector4<T> &v ) 
	{ 
		x += v.x; y += v.y; z += v.z; w += v.w; 
	}

	void operator -=( const Vector4<T> &v ) 
	{ 
		x -= v.x; y -= v.y; z -= v.z; w -= v.w; 
	}

	void operator *=( const Vector4<T> &v ) 
	{ 
		x *= v.x; y *= v.y; z *= v.z; 
	}
/*
	void operator *=( const Matrix &mat ) const
	{
		T _x, _y, _z, _w;
		
		_x = x*mat._11 + y*mat._21 + z*mat._31 + mat._41;
		_y = x*mat._12 + y*mat._22 + z*mat._32 + mat._42;
		_z = x*mat._13 + y*mat._23 + z*mat._33 + mat._43;
		_w = x*mat._14 + y*mat._24 + z*mat._34 + mat._44;

		x = _x/_w;
		y = _y/_w;
		z = _z/_w;
		w = 1.0f;
	}
*/
	void operator /=( const Vector4<T> &v ) 
	{ 
		x /= v.x; y /= v.y; z /= v.z; 
	}

	Vector4<T> operator +( const Vector4<T> &v ) const 
	{ 
		return IVector( x+v.x, y+v.y, z+v.z ); 
	}

	Vector4<T> operator -( const Vector4<T> &v ) const 
	{ 
		return IVector( x-v.x, y-v.y, z-v.z ); 
	}

	Vector4<T> operator *( T f ) const
	{ 
		return IVector ( x*f, y*f, z*f ); 
	}
/*
	Vector4<T> operator *( const Matrix &mat ) const
	{
		Vector4<T> vec;
		
		vec.x = x*mat._11 + y*mat._21 + z*mat._31 + mat._41;
		vec.y = x*mat._12 + y*mat._22 + z*mat._32 + mat._42;
		vec.z = x*mat._13 + y*mat._23 + z*mat._33 + mat._43;
		vec.w = x*mat._14 + y*mat._24 + z*mat._34 + mat._44;

		vec.x = vec.x/vec.w;
		vec.y = vec.y/vec.w;
		vec.z = vec.z/vec.w;
		vec.w = 1.0f;

		return vec;
	}
*/
	inline  T	operator *( const Vector4<T> &v ) const
	{ 
		return ( x*v.x + y*v.y + z*v.z ); 
	}
		
};

//! A not very complete Vector class
template <class T>
class Vector3
{
public:
	T x, y, z;

	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Vector3( T _x, T _y, T _z ) { x = _x; y = _y; z = _z; }

	inline void Set( T _x, T _y, T _z ) { x = _x; y = _y; z = _z; }

	inline T	GetLength( void ) { return (T) sqrt( x*x + y*y + z*z ); }

	inline T	GetSqrLength( void ) { return ( x*x + y*y + z*z); }

	inline void Cross( const Vector3 &v1, const Vector3 &v2 ) 
	{
		x = v1.y*v2.z - v1.z*v2.y;
		y = v1.z*v2.x - v1.x*v2.z;
		z = v1.x*v2.y - v1.y*v2.x;
	}

	inline void Normalize( void )
	{
		// Bugs fixed: it used to be = T f = (T)(x*x + y*y + z*z); see: 
		// no sqrt caused Matrix::buildViewMatrix get the wrong result
		T f = (T)sqrt( x*x + y*y + z*z );
		x /= f; y /= f; z /= f;
	}

	inline T	AngleWith( Vector3 &v )
	{
		return (T) acos( ((*this)*v) / (this->GetLength()*v.GetLength()) );
	}

	inline void Sub( const Vector3 &v1, const Vector3 &v2 )
	{
		x = v2.x - v1.x;
		y = v2.y - v1.y;
		z = v2.z - v1.z;
	}

	void operator +=( const Vector3 &v ) 
	{
		x += v.x; y += v.y; z += v.z;
	}

	void operator -=( const Vector3 &v )
	{
		x -= v.x; y -= v.y; z -= v.z;
	}

	void operator *=( const Vector3 &v )
	{
		x *= v.x; y *= v.y; z *= v.z;
	}

	void operator *=( T value )
	{
		x *= value; y *= value; z *= value;
	}
/*
	void operator *=( const Matrix &mat ) const
	{
		T _x, _y, _z;
		
		_x = x*mat._11 + y*mat._21 + z*mat._31 + mat._41;
		_y = x*mat._12 + y*mat._22 + z*mat._32 + mat._42;
		_z = x*mat._13 + y*mat._23 + z*mat._33 + mat._43;

		x = _x; y = _y; z = _z;
	}
*/
	void operator /=( const Vector3 &v )
	{
		x /= v.x; y /= v.y; z /= v.z;
	}

	Vector3 operator +( const Vector3 &v ) const
	{
		return Vector3<T>( x+v.x, y+v.y, z+v.z );
	}

	Vector3 operator -( const Vector3 &v ) const
	{
		return Vector3<T>( x-v.x, y-v.y, z-v.z );
	}

	Vector3 operator *( T f ) const
	{
		return Vector3<T> ( x*f, y*f, z*f );
	}
/*
	Vector3 operator *( const Matrix &mat ) const
	{
		Vector3<T> vec;
		T w;
		
		vec.x = x*mat._11 + y*mat._21 + z*mat._31 + mat._41;
		vec.y = x*mat._12 + y*mat._22 + z*mat._32 + mat._42;
		vec.z = x*mat._13 + y*mat._23 + z*mat._33 + mat._43;
		w	  = (T)(x*mat._14 + y*mat._24 + z*mat._34 + mat._44);
		
		vec.x = vec.x/w;
		vec.y = vec.y/w;
		vec.z = vec.z/w;

		return vec;
	}
*/
	inline  T	operator *( const Vector3 &v ) const
	{
		return (x*v.x + y*v.y + z*v.z );
	}
		
};	

template <class T>
class Vector2
{
public:
	T x, y;

	Vector2() { x = 0.0f; y = 0.0f; }
	Vector2( T _x, T _y ) { x = _x; y = _y; }

	inline void Set( T _x, T _y ) { x = _x; y = _y; }

	inline T	GetLength( void ) { return (T) sqrt( x*x + y*y ); }

	inline T	GetSqrLength( void ) { return ( x*x + y*y ); }

	inline void Cross( const Vector2 &v1, const Vector2 &v2 )
	{
		x = v1.y*v2.z - v1.z*v2.y;
		y = v1.z*v2.x - v1.x*v2.z;
	}

	inline void Normalize( void )
	{
		T f = (T)sqrt(x*x + y*y );
		x /= f; y /= f;
	}

	inline T	AngleWith( Vector2 &v )
	{
		return (T) acos( ((*this)*v) / (this->GetLength()*v.GetLength()) );
	}

	inline void Sub( const Vector2 &v1, const Vector2 &v2 )
	{
		x = v2.x - v1.x;
		y = v2.y - v1.y;
	}

	void operator +=( const Vector2 &v )
	{
		x += v.x; y += v.y;
	}

	void operator -=( const Vector2 &v )
	{
		x -= v.x; y -= v.y;
	}

	void operator *=( const Vector2 &v )
	{
		x *= v.x; y *= v.y;
	}

	void operator /=( const Vector2 &v )
	{
		x /= v.x; y /= v.y;
	}

	Vector2 operator +( const Vector2 &v ) const
	{
		return Vector2<T>( x+v.x, y+v.y );
	}

	Vector2 operator -( const Vector2 &v ) const
	{
		return Vector2<T>( x-v.x, y-v.y );
	}

	Vector2 operator *( T f ) const
	{
		return Vector2<T> ( x*f, y*f );
	}

	inline  T	operator *( const Vector2 &v ) const
	{
		return (x*v.x + y*v.y );
	}
};

typedef Vector4<s32> Vector4i;
typedef Vector4<f32> Vector4f;
typedef Vector3<s32> Vector3i;
typedef Vector3<f32> Vector3f;
typedef Vector2<s32> Vector2i;
typedef Vector2<f32> Vector2f;

}	// namespace core
}	// namespace inveria

#endif	// _VECTOR_H_
