#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Types.h"
#include "Vector.h"

#include <math.h>
#include <string.h>

namespace inveria
{
namespace core
{

//! Wow, i've been thinking is it necessary to add the scalar matrix addition?
//! well, i suppose maybe i'll need it later, so i just put it down here.
//! Those codes below is big enough to kill your hunger.
//! I've been thinking to add the SSE code to enhance some calculation in parallel calc.
//! There are lots of operator used in this class. ^_^ Suhendra Ahmad(ceo @ ainasoft.com)
class Matrix
{
public:

	f32 _11, _12, _13, _14;
	f32 _21, _22, _23, _24;
	f32 _31, _32, _33, _34;
	f32 _41, _42, _43, _44;

	Matrix( void ) 
	{  
		Identity();		
	};

	Matrix( const Matrix &mat )
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
	};

	Vector3f operator *( const Vector3f &vec ) const
	{
		Vector3f result;

		result.x = vec.x*_11 + vec.y*_21 + vec.z*_31 + _41;
		result.y = vec.x*_12 + vec.y*_22 + vec.z*_32 + _42;
		result.z = vec.x*_13 + vec.y*_23 + vec.z*_33 + _43;

		return result;
	};
	
	Matrix operator *( const Matrix &mat ) const
	{
		Matrix m;
		
		m._11 = _11*mat._11 + _12*mat._21 + _13*mat._31 + _14*mat._41;
		m._12 = _11*mat._12 + _12*mat._22 + _13*mat._32 + _14*mat._42;
		m._13 = _11*mat._13 + _12*mat._23 + _13*mat._33 + _14*mat._43;
		m._14 = _11*mat._14 + _12*mat._24 + _13*mat._34 + _14*mat._44;

		m._21 = _21*mat._11 + _22*mat._21 + _23*mat._31 + _24*mat._41;
		m._22 = _21*mat._12 + _22*mat._22 + _23*mat._32 + _24*mat._42;
		m._23 = _21*mat._13 + _22*mat._23 + _23*mat._33 + _24*mat._43;
		m._24 = _21*mat._14 + _22*mat._24 + _23*mat._34 + _24*mat._44;

		m._31 = _31*mat._11 + _32*mat._21 + _33*mat._31 + _34*mat._41;
		m._32 = _31*mat._12 + _32*mat._22 + _33*mat._32 + _34*mat._42;
		m._33 = _31*mat._13 + _32*mat._23 + _33*mat._33 + _34*mat._43;
		m._34 = _31*mat._14 + _32*mat._24 + _33*mat._34 + _34*mat._44;

		m._41 = _41*mat._11 + _42*mat._21 + _43*mat._31 + _44*mat._41;
		m._42 = _41*mat._12 + _42*mat._22 + _43*mat._32 + _44*mat._42;
		m._43 = _41*mat._13 + _42*mat._23 + _43*mat._33 + _44*mat._43;
		m._44 = _41*mat._14 + _42*mat._24 + _43*mat._34 + _44*mat._44;

		return m;
	};

	Matrix operator *( f32 val ) const
	{
		Matrix m;
		
		m._11 = _11*val; m._12 = _12*val; m._13 = _13*val; m._14 = _14*val;
		m._21 = _21*val; m._22 = _22*val; m._23 = _23*val; m._24 = _24*val;
		m._31 = _31*val; m._32 = _32*val; m._33 = _33*val; m._34 = _34*val;
		m._41 = _41*val; m._42 = _42*val; m._43 = _43*val; m._44 = _44*val;
	
		return m;	
	};

	Matrix operator /( f32 val ) const
	{
		if (val == 0) return (*this);

		Matrix m;
		
		m._11 = _11/val; m._12 = _12/val; m._13 = _13/val; m._14 = _14/val;
		m._21 = _21/val; m._22 = _22/val; m._23 = _13/val; m._24 = _24/val;
		m._31 = _31/val; m._32 = _32/val; m._33 = _13/val; m._34 = _34/val;
		m._41 = _41/val; m._42 = _42/val; m._43 = _13/val; m._44 = _44/val;
	
		return m;	
	};

	Matrix operator +( f32 val ) const
	{
		Matrix m;
		
		m._11 = _11+val; m._12 = _12+val; m._13 = _13+val; m._14 = _14+val;
		m._21 = _21+val; m._22 = _22+val; m._23 = _23+val; m._24 = _24+val;
		m._31 = _31+val; m._32 = _32+val; m._33 = _33+val; m._34 = _34+val;
		m._41 = _41+val; m._42 = _42+val; m._43 = _43+val; m._44 = _44+val;
	
		return m;	
	};

	Matrix operator -( f32 val ) const
	{
		Matrix m;
		
		m._11 = _11-val; m._12 = _12-val; m._13 = _13-val; m._14 = _14-val;
		m._21 = _21-val; m._22 = _22-val; m._23 = _23-val; m._24 = _24-val;
		m._31 = _31-val; m._32 = _32-val; m._33 = _33-val; m._34 = _34-val;
		m._41 = _42-val; m._42 = _42-val; m._43 = _43-val; m._44 = _44-val;
	
		return m;
	};

	Matrix operator +( const Matrix &mat ) const
	{
		Matrix m;
		
		m._11 = _11+mat._11; m._12 = _12+mat._12; m._13 = _13+mat._13; m._14 = _14+mat._14;
		m._21 = _21+mat._21; m._22 = _22+mat._22; m._23 = _23+mat._23; m._24 = _24+mat._24;
		m._31 = _31+mat._31; m._32 = _32+mat._32; m._33 = _33+mat._33; m._34 = _34+mat._34;
		m._41 = _41+mat._41; m._42 = _42+mat._42; m._43 = _43+mat._43; m._44 = _44+mat._44;

		return m;	
	};
	
	Matrix operator -( const Matrix &mat ) const
	{
		Matrix m;
		
		m._11 = _11-mat._11; m._12 = _12-mat._12; m._13 = _13-mat._13; m._14 = _14-mat._14;
		m._21 = _21-mat._21; m._22 = _22-mat._22; m._23 = _23-mat._23; m._24 = _24-mat._24;
		m._31 = _31-mat._31; m._32 = _32-mat._32; m._33 = _33-mat._33; m._34 = _34-mat._34;
		m._41 = _41-mat._41; m._42 = _42-mat._42; m._43 = _43-mat._43; m._44 = _44-mat._44;

		return m;
	};

    inline  void operator *=( const Matrix &mat )
	{
		Matrix m;
	
		m._11 = _11*mat._11 + _12*mat._21 + _13*mat._31 + _14*mat._41;
		m._12 = _11*mat._12 + _12*mat._22 + _13*mat._32 + _14*mat._42;
		m._13 = _11*mat._13 + _12*mat._23 + _13*mat._33 + _14*mat._43;
		m._14 = _11*mat._14 + _12*mat._24 + _13*mat._34 + _14*mat._44;

		m._21 = _21*mat._11 + _22*mat._21 + _23*mat._31 + _24*mat._41;
		m._22 = _21*mat._12 + _22*mat._22 + _23*mat._32 + _24*mat._42;
		m._23 = _21*mat._13 + _22*mat._23 + _23*mat._33 + _24*mat._43;
		m._24 = _21*mat._14 + _22*mat._24 + _23*mat._34 + _24*mat._44;
	
		m._31 = _31*mat._11 + _32*mat._21 + _33*mat._31 + _34*mat._41;
		m._32 = _31*mat._12 + _32*mat._22 + _33*mat._32 + _34*mat._42;
		m._33 = _31*mat._13 + _32*mat._23 + _33*mat._33 + _34*mat._43;
		m._34 = _31*mat._14 + _32*mat._24 + _33*mat._34 + _34*mat._44;

		m._41 = _41*mat._11 + _42*mat._21 + _43*mat._31 + _44*mat._41;
		m._42 = _41*mat._12 + _42*mat._22 + _43*mat._32 + _44*mat._42;
		m._43 = _41*mat._13 + _42*mat._23 + _43*mat._33 + _44*mat._43;
		m._44 = _41*mat._14 + _42*mat._24 + _43*mat._34 + _44*mat._44;

		(*this) = m; 
	};

	inline  void operator *=( f32 val )
	{
		_11 *= val; _12 *= val; _13 *= val; _14 *= val;
		_21 *= val; _22 *= val; _23 *= val; _24 *= val;
		_31 *= val; _32 *= val; _33 *= val; _34 *= val;
		_41 *= val; _42 *= val; _43 *= val; _44 *= val;	
	};

	inline  void operator /=( f32 val )
	{
		if (val == 0) return;
	
		_11 /= val; _12 /= val; _13 /= val; _14 /= val;
		_21 /= val; _22 /= val; _23 /= val; _24 /= val;
		_31 /= val; _32 /= val; _33 /= val; _34 /= val;
		_41 /= val; _42 /= val; _43 /= val; _44 /= val;	
	};

	inline  void operator +=( f32 val )
	{
		_11 += val; _12 += val; _13 += val; _14 += val;
		_21 += val; _22 += val; _23 += val; _24 += val;
		_31 += val; _32 += val; _33 += val; _34 += val;
		_41 += val; _42 += val; _43 += val; _44 += val;	
	};

	inline	void operator -=( f32 val )
	{
		_11 -= val; _12 -= val; _13 -= val; _14 -= val;
		_21 -= val; _22 -= val; _23 -= val; _24 -= val;
		_31 -= val; _32 -= val; _33 -= val; _34 -= val;
		_41 -= val; _42 -= val; _43 -= val; _44 -= val;	
	};

	inline  void operator +=( const Matrix &mat )
	{
		_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
		_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
		_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
		_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
	};

	inline	void operator -=( const Matrix &mat )
	{
		_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
		_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
		_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
		_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
	};

	inline	bool operator ==( const Matrix &mat ) const
	{
		if ((mat._11 != _11) || (mat._12 != _12) || (mat._13 != _13) || (mat._14 != _14) ||
			(mat._21 != _21) || (mat._22 != _22) || (mat._23 != _23) || (mat._24 != _24) ||
			(mat._31 != _31) || (mat._32 != _32) || (mat._33 != _33) || (mat._34 != _34) ||
			(mat._41 != _41) || (mat._42 != _42) || (mat._43 != _43) || (mat._44 != _44))
			return false;

		return true;
	};

	inline	bool operator !=( const Matrix &mat ) const
	{
		if ((mat._11 == _11) && (mat._12 == _12) && (mat._13 == _13) && (mat._14 == _14) &&
			(mat._21 == _21) && (mat._22 == _22) && (mat._23 == _23) && (mat._24 != _24) &&
			(mat._31 == _31) && (mat._32 == _32) && (mat._33 == _33) && (mat._34 != _34) &&
			(mat._41 == _41) && (mat._42 == _42) && (mat._43 == _43) && (mat._44 != _44))
			return false;

		return true;
	};

	inline  void operator =( const Matrix &mat )
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
	};
	
	inline void Identity( void )
	{
		f32 *f = (f32 *)&this->_11;
		memset(f, 0, sizeof(Matrix));
		_11 = _22 = _33 = _44 = 1.0f;	
	};

	inline void Zero( void )
	{
		f32 *f = (f32 *)&this->_11;
		memset(f, 0, sizeof(Matrix));
	};

	inline void Transpose( void )
	{
		Matrix m;

		m._11 = _11; m._12 = _21; m._13 = _31; m._14 = _41;
		m._21 = _12; m._22 = _22; m._23 = _32; m._24 = _42;
		m._31 = _13; m._32 = _23; m._33 = _33; m._34 = _43;
		m._41 = _14; m._42 = _24; m._43 = _34; m._44 = _44;
	
		(*this) = m;
	};

	inline void TransposeOf( const Matrix &m )
	{
		_11 = m._11; _12 = m._21; _13 = m._31; _14 = m._41;
		_21 = m._12; _22 = m._22; _23 = m._32; _24 = m._42;
		_31 = m._13; _32 = m._23; _33 = m._33; _34 = m._43;
		_41 = m._14; _42 = m._24; _43 = m._34; _44 = m._44;
	};

	inline void RotateX( f32 angle )
	{
        f32	fCos = cosf( angle );
		f32 fSin = sinf( angle );

		_22 = fCos;
		_23 = fSin;
		_32 = -fSin;
		_33 = fCos;
		_12 = _13 = _14 = _21 = _24 = _31 = _34 = _41 = _42 = _43 = 0.0f;
		_11 = _44 = 1.0f;
	};

	inline void RotateY( f32 angle )
	{
		f32 fCos = cosf( angle );
		f32 fSin = sinf( angle );

		_11 = fCos;
		_13 = -fSin;
		_31 = fSin;
		_33 = fCos;
		_22 = _44 = 1.0f;
		_12 = _14 = _23 = _21 = _24 = _32 = _34 = _42 = _42 = _43 = 0.0f;
	};

	inline void RotateZ( f32 angle )
	{
		f32 fCos = cosf( angle );
		f32 fSin = sinf( angle );

		_11 = fCos;
		_12 = fSin;
		_21 = -fSin;
		_22 = fCos;
		_33 = _44 = 1.0f;
		_13 = _14 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f;
	};

	inline void Translate( f32 x, f32 y, f32 z )
	{
		_41 = x;
		_42 = y;
		_43 = z;
	};

	inline void InverseOf( const Matrix &mat )
	{
		Matrix mTrans;
		f32		fTemp[12],  // cofactors
				fDet;

		// calculate transposed matrix
		mTrans.TransposeOf(mat);

		// 8 Kofaktor
		fTemp[ 0] = mTrans._33 * mTrans._44;
		fTemp[ 1] = mTrans._34 * mTrans._43;
		fTemp[ 2] = mTrans._32 * mTrans._44;
		fTemp[ 3] = mTrans._34 * mTrans._42;
		fTemp[ 4] = mTrans._32 * mTrans._43;
		fTemp[ 5] = mTrans._33 * mTrans._42;
		fTemp[ 6] = mTrans._31 * mTrans._44;
		fTemp[ 7] = mTrans._34 * mTrans._41;
		fTemp[ 8] = mTrans._31 * mTrans._43;
		fTemp[ 9] = mTrans._33 * mTrans._41;
		fTemp[10] = mTrans._31 * mTrans._42;
		fTemp[11] = mTrans._32 * mTrans._41;

		_11  = fTemp[0]*mTrans._22 + fTemp[3]*mTrans._23 + fTemp[4] *mTrans._24;
		_11 -= fTemp[1]*mTrans._22 + fTemp[2]*mTrans._23 + fTemp[5] *mTrans._24;
		_12  = fTemp[1]*mTrans._21 + fTemp[6]*mTrans._23 + fTemp[9] *mTrans._24;
		_12 -= fTemp[0]*mTrans._21 + fTemp[7]*mTrans._23 + fTemp[8] *mTrans._24;
		_13  = fTemp[2]*mTrans._21 + fTemp[7]*mTrans._22 + fTemp[10]*mTrans._24;
		_13 -= fTemp[3]*mTrans._21 + fTemp[6]*mTrans._22 + fTemp[11]*mTrans._24;
		_14  = fTemp[5]*mTrans._21 + fTemp[8]*mTrans._22 + fTemp[11]*mTrans._23;
		_14 -= fTemp[4]*mTrans._21 + fTemp[9]*mTrans._22 + fTemp[10]*mTrans._23;
		_21  = fTemp[1]*mTrans._12 + fTemp[2]*mTrans._13 + fTemp[5] *mTrans._14;
		_21 -= fTemp[0]*mTrans._12 + fTemp[3]*mTrans._13 + fTemp[4] *mTrans._14;
		_22  = fTemp[0]*mTrans._11 + fTemp[7]*mTrans._13 + fTemp[8] *mTrans._14;
		_22 -= fTemp[1]*mTrans._11 + fTemp[6]*mTrans._13 + fTemp[9] *mTrans._14;
		_23  = fTemp[3]*mTrans._11 + fTemp[6]*mTrans._12 + fTemp[11]*mTrans._14;
		_23 -= fTemp[2]*mTrans._11 + fTemp[7]*mTrans._12 + fTemp[10]*mTrans._14;
		_24  = fTemp[4]*mTrans._11 + fTemp[9]*mTrans._12 + fTemp[10]*mTrans._13;
		_24 -= fTemp[5]*mTrans._11 + fTemp[8]*mTrans._12 + fTemp[11]*mTrans._13;

		fTemp[ 0]  = mTrans._13 * mTrans._24;
		fTemp[ 1]  = mTrans._14 * mTrans._23;
		fTemp[ 2]  = mTrans._12 * mTrans._24;
		fTemp[ 3]  = mTrans._14 * mTrans._22;
		fTemp[ 4]  = mTrans._12 * mTrans._23;
		fTemp[ 5]  = mTrans._13 * mTrans._22;
		fTemp[ 6]  = mTrans._11 * mTrans._24;
		fTemp[ 7]  = mTrans._14 * mTrans._21;
		fTemp[ 8]  = mTrans._11 * mTrans._23;
		fTemp[ 9]  = mTrans._13 * mTrans._21;
		fTemp[10]  = mTrans._11 * mTrans._22;
		fTemp[11]  = mTrans._12 * mTrans._21;

		_31  = fTemp[0] *mTrans._42 + fTemp[3] *mTrans._43 + fTemp[4] *mTrans._44;
		_31 -= fTemp[1] *mTrans._42 + fTemp[2] *mTrans._43 + fTemp[5] *mTrans._44;
		_32  = fTemp[1] *mTrans._41 + fTemp[6] *mTrans._43 + fTemp[9] *mTrans._44;
		_32 -= fTemp[0] *mTrans._41 + fTemp[7] *mTrans._43 + fTemp[8] *mTrans._44;
		_33  = fTemp[2] *mTrans._41 + fTemp[7] *mTrans._42 + fTemp[10]*mTrans._44;
		_33 -= fTemp[3] *mTrans._41 + fTemp[6] *mTrans._42 + fTemp[11]*mTrans._44;
		_34  = fTemp[5] *mTrans._41 + fTemp[8] *mTrans._42 + fTemp[11]*mTrans._43;
		_34 -= fTemp[4] *mTrans._41 + fTemp[9] *mTrans._42 + fTemp[10]*mTrans._43;
		_41  = fTemp[2] *mTrans._33 + fTemp[5] *mTrans._34 + fTemp[1] *mTrans._32;
		_41 -= fTemp[4] *mTrans._34 + fTemp[0] *mTrans._32 + fTemp[3] *mTrans._33;
		_42  = fTemp[8] *mTrans._34 + fTemp[0] *mTrans._31 + fTemp[7] *mTrans._33;
		_42 -= fTemp[6] *mTrans._33 + fTemp[9] *mTrans._34 + fTemp[1] *mTrans._31;
		_43  = fTemp[6] *mTrans._32 + fTemp[11]*mTrans._34 + fTemp[3] *mTrans._31;
		_43 -= fTemp[10]*mTrans._34 + fTemp[2] *mTrans._31 + fTemp[7] *mTrans._32;
		_44  = fTemp[10]*mTrans._33 + fTemp[4] *mTrans._31 + fTemp[9] *mTrans._32;
		_44 -= fTemp[8] *mTrans._32 + fTemp[11]*mTrans._33 + fTemp[5] *mTrans._31;

		fDet = mTrans._11*_11 + 
			   mTrans._12*_12 + 
			   mTrans._13*_13 +
               mTrans._14*_14;

		fDet = 1/fDet;

		_11 *= fDet;  
		_12 *= fDet;  
		_13 *= fDet;  
		_14 *= fDet;

		_21 *= fDet;  
		_22 *= fDet;  
		_23 *= fDet;  
		_24 *= fDet;

		_31 *= fDet;  
		_32 *= fDet;  
		_33 *= fDet;  
		_34 *= fDet;

		_41 *= fDet;  
		_42 *= fDet;  
		_43 *= fDet;  
		_44 *= fDet;
	}

	/********************************************************************************
	  The projection matrix i use here maybe a bit different
	  with the other game engine, but you can use another kind
	  of projection by replacing the w, h value and keep 
	  the q value like this :
			
			f32 h = (f32)( cosf( fov/2 ) / sinf( fov/2 ) );
			f32 w = h / aspectRatio;
			f32	q = far / (far-near)

			And then apply to this matrix:
			================================

			| 2*near/w	0			0			0 |	
			| 0			2*near/h	0			0 |
			| 0			0			q			1 |  
			| 0			0			q*near		0 |

			Or into this kind of matrix:
			================================
			| 2*near/w	0			0		0		|	
			| 0			2*near/h	0		0		|
			| 0			0			q		q*near  | 
			| 0			0			1		0		|
			
    
	  But those codes above, i have it from a peek from another game engine 
	  source code, so i'm not guarantee that those code above will work 
	  under AhmadENGINE, so i  recommend you to use my kind of perspective 
	  projection matrix, and you know what? it works very well. 

	  It's quite hard to calculate the formulas, and i'm still wondering
	  where did i get those formulas, you ask? my answer is i don't know either.
	  I'm not a mathematician, i'm just a stupid guy whose trying to learn how
	  to get things right in 3D game engine.
	  As i say previously, i'm a newbie man.

	  For all newbies out there.. If you still don't understand where did
	  those number came from, my suggestion is keep learning with patience.
	  Dig some more.. and say: give me more.. give me more.. i want more..

	  *** Impatience is the mother of stupidity ***

	  *_* Suhendra Ahmad (ceo @ ainasoft.com)
	  
	  Updated on <Wed, December 7th 2005 1:18am>
	
	********************************************************************************/

	//! Build a projection matrix for left handed coordinate system (D3D)
	inline void BuildPerspectiveProjectionMatrixLH( f32 fov, f32 aspectRatio, f32 nearPlane, f32 farPlane )
	{
		f32 fovDegree = fov * PI / 180;
		f32 fSin = sinf( fovDegree/2 );
		if (fSin < EPSILON) return;
		f32 deltaPlane = (farPlane - nearPlane);
		if (deltaPlane < EPSILON) return;

		f32 h = (f32)( cosf( fovDegree/2 ) / fSin );
		f32 w = h / aspectRatio;
		f32 q = farPlane / deltaPlane;

		Identity();

		_11 = w;
		_22 = h;
		_33 = q;
		_34 = 1;
		_43 = -q*nearPlane;
	};

	//! Build a projection matrix for right handed coordinate system (OpenGL?)
	inline void BuildPerspectiveProjectionMatrixRH( f32 fov, f32 aspectRatio, f32 nearPlane, f32 farPlane )
	{
		f32 fovDegree = fov * PI / 180;
		f32 fSin = sinf( fovDegree/2 );
		if (fSin < EPSILON) return;
		f32 deltaPlane = (farPlane - nearPlane);
		if (deltaPlane < EPSILON) return;
		
		f32 h = (f32)( cosf( fovDegree/2 ) / fSin );
		f32 w = h / aspectRatio;
		f32 q = farPlane / deltaPlane;
        
		Identity();

		_11 = w;
		_22 = h;
		_33 = q;
		_34 = -1;
		_43 = -q*nearPlane;
	};

	//! Build a view matrix 
	inline void BuildViewMatrix( const Vector3f &cameraPos, const Vector3f &lookAt, const Vector3f &up )
	{
		Vector3f zaxis = lookAt - cameraPos;
		zaxis.Normalize();

		Vector3f xaxis;
		xaxis.Cross( up, zaxis );
		xaxis.Normalize();

		Vector3f yaxis;
		yaxis.Cross( zaxis, xaxis );

		Identity();

		_11 = xaxis.x;
		_21 = xaxis.y;
		_31 = xaxis.z;
		_41 = -(xaxis*cameraPos);
		_12 = yaxis.x;
		_22 = yaxis.y;
		_32 = yaxis.z;
		_42 = -(yaxis*cameraPos);
		_13 = zaxis.x;
		_23 = zaxis.y;
		_33 = zaxis.z;
		_43 = -(zaxis*cameraPos);
	};

	//! Build Orthogonal Projection Matrix
	inline void BuildOrthogonalProjectionMatrix( u32 nWidth, u32 nHeight, f32 nearPlane, f32 farPlane )
	{
		if ( (nWidth < EPSILON) || (nHeight < EPSILON) || (farPlane - nearPlane < EPSILON) ) return;
		f32 w = (f32)2.0f/nWidth;
		f32 h = (f32)2.0f/nHeight;
		f32 q = 1.0f/(farPlane - nearPlane);

		Identity();

		_11 = w;
		_22 = h;
		_33 = q;
		_43 = -nearPlane*q;

	};

	inline void BuildFrustum( f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar )
	{
		f32 dx, dy, dz;

		dx = right - left;
		dy = bottom - top;
		dz = zfar - znear;
		
		if ( ( dx < EPSILON ) || ( dy < EPSILON ) || ( dz < EPSILON ) || ( znear < 0 ) || ( zfar < 0 ) )
			return;

		Identity();

		_11 = znear * 2.0f / dx;
		_12 = _13 = _14 = 0.0f;

		_22 = znear * 2.0f / dy;
		_21 = _23 = _24 = 0.0f;

		_31 = ( right + left ) / dx;
		_32 = ( top + bottom ) / dy;
		_33 = ( zfar + znear ) / dz;
		_34 = 1.0f;
		
		_43 = znear * zfar / dz;
		_41 = _42 = _44 = 0.0f;
	};

	// Beware, this matrix is tweaked by me for OpenGL, well i don't know if it's working for Direct3D
	// Created and tweaked by Suhendra Ahmad on Fri, April 11 2007 12:30am
	inline void BuildOrthogonalMatrix( f32 left, f32 right, f32 top, f32 bottom, f32 znear, f32 zfar )
	{
		f32 dx, dy, dz;

		dx = right - left;
		dy = bottom - top;
		dz = zfar - znear;

		if ( ( dx < EPSILON ) || ( dy < EPSILON ) || ( dz < EPSILON ) || ( znear < 0 ) || ( zfar < 0 ) )
			return;

		Identity();

		_11 = 2.0f / dx;
		_22 = 2.0f / dy;
		_33 = 2.0f / dz;

		_41 = -( right + left ) / dx;
		_42 = ( top + bottom ) / dy;	// + because we're not substracting, by adding up (remember cartesian rule)
		_43 = -( zfar + znear ) / dz;
	};

};

}	// namespace core
}	// namespace inveria

#endif // _MATRIX_H_
