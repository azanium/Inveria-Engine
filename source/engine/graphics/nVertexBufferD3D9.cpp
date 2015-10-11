#include "nVertexBufferD3D9.h"
#include <Windows.h>

namespace inveria
{
namespace graphics
{

nVertexBufferD3D9::nVertexBufferD3D9()
{
	mpVB = 0;
	mbIsLocked = 0;
}

nVertexBufferD3D9::nVertexBufferD3D9( iRenderer* renderer, u32 numVerts, u32 vertexFormat, u32 vertexSize, E_VERTEX_TYPE vertexType, E_BUFFER_TYPE bufferType )
{
	mpRenderer = renderer;
	mnNumVerts = numVerts;
	mnVertexFormat = vertexFormat;
	mnVertexSize = vertexSize;
	meBufferType = bufferType;
	meVertexType = vertexType;
	mbIsLocked = false;
	mpVB = 0;
}

nVertexBufferD3D9::~nVertexBufferD3D9()
{
	if ( mbIsLocked ) unlock();

	SAFE_RELEASE( mpVB );
}

void* nVertexBufferD3D9::lock( u32 startVertex , u32 endVertex )
{
	if ( !mpVB || mbIsLocked ) return 0;

	u32 flags = 0;

	switch ( meBufferType )
	{
	case EBT_STATIC_BUFFER:
		break;

	case EBT_DYNAMIC_BUFFER:
		flags |= D3DLOCK_DISCARD;
	}

	HRESULT hr = mpVB->Lock( startVertex * mnVertexSize, ( endVertex - startVertex ) * mnVertexSize, &mpLockedPtr, flags );

	DEBUG_BREAK( FAILED( hr ) );

	mbIsLocked = true;

	return mpLockedPtr;
}

void nVertexBufferD3D9::unlock()
{
	DEBUG_BREAK( mpVB->Unlock() );

	mbIsLocked = false;
}

void nVertexBufferD3D9::activate()
{
	if ( mpVB && !mbIsLocked )
		mpRenderer->setVertexBuffer( this );
}

}	// namespace graphics
}	// namespace inveria
