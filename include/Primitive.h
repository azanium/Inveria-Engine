#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "Buyut.h"
#include "iRenderer.h"
#include "iVertexBuffer.h"
#include "iIndexBuffer.h"

namespace inveria
{
namespace graphics
{

// This is a helper class, shouldn't be put on the .cpp file
// It will make my life easier -Suhendra
template < class T >
class Primitive: public Buyut
{
protected:
	iVertexBuffer*	mpVB;
	iIndexBuffer*	mpIB;
	iRenderer*		mpRenderer;

public:
	Primitive( iRenderer* renderer, u32 numVertices, u32 numIndices, E_BUFFER_TYPE bufferType ) 
	{
		mpVB = renderer->createVertexBuffer( numVertices, getVertexType( ( T* )NULL ), bufferType );
		mpIB = renderer->createIndexBuffer( numIndices, bufferType );
	};

	virtual ~Primitive()
	{
		SAFE_THROW( mpVB );
		SAFE_THROW( mpIB );
	}

	virtual T* lockVB( u32 startVertex = 0, u32 endVertex = 0 )
	{
		if ( mpVB )
		{
			return static_cast< T* >( mpVB->lock( startVertex, endVertex ) );
		}

		return 0;
	};

	virtual u16* lockIB( u32 startIndex = 0, u32 endIndex = 0 )
	{
		if ( mpIB )
		{
			return static_cast< u16* >( mpIB->lock( startIndex, endIndex ) );
		}

		return 0;
	};

	virtual void unlockVB()
	{
		mpVB->unlock();
	};

	virtual void unlockIB()
	{
		mpIB->unlock();
	};

	virtual void copyVBFromArray( const T* vbArray, u32 vbSize )
	{
		if ( !mpVB->isValid() ) return;
		T* vb = lockVB();
		if ( vb )
		{
			memcpy( vb, vbArray, vbSize * sizeof( T ) );
			unlockVB();
		}
	};

	virtual void copyIBFromArray( const u16* ibArray, u32 ibSize )
	{
		if ( !mpIB->isValid() ) return;

		u16* ib = lockIB();
		if ( ib ) 
		{
			memcpy( ib, ibArray, ibSize * sizeof( T ) );
			unlockIB();
		}
	};

	virtual void activate()
	{
		mpVB->activate();
		mpIB->activate();
	};

	virtual iVertexBuffer* getVertexBuffer()
	{
		return mpVB;
	};

	virtual iIndexBuffer* getIndexBuffer()
	{
		return mpIB;
	};
};

}	// namespace graphics
}	// namespace inveria

#endif	// _PRIMITIVE_H_