#include "nIndexBufferD3D9.h"

namespace inveria
{
namespace graphics
{

nIndexBufferD3D9::nIndexBufferD3D9( iRenderer* renderer, u32 indexCount, E_BUFFER_TYPE bufferType )
{
	meBufferType = bufferType;
	mpRenderer = renderer;
	mnNumIndices = indexCount;
	mbIsLocked = false;
	mpIB = 0;
}

nIndexBufferD3D9::~nIndexBufferD3D9()
{
	if ( mbIsLocked ) unlock();

	SAFE_RELEASE( mpIB );
}

void* nIndexBufferD3D9::lock( u32 startIndex, u32 endIndex )
{
	if ( !mpIB || mbIsLocked ) return 0;

	u32 flags = 0;
    
	switch ( meBufferType )
	{
	case EBT_STATIC_BUFFER:
		break;

	case EBT_DYNAMIC_BUFFER:
		flags |= D3DLOCK_DISCARD;
		break;
	}

	HRESULT hr = mpIB->Lock( sizeof( u16 ) * startIndex, sizeof( u16 ) * ( endIndex - startIndex ), &mpLockedPtr, flags );

	DEBUG_BREAK( FAILED( hr ) );
	
	mbIsLocked = true;

	return mpLockedPtr;
}

void nIndexBufferD3D9::unlock()
{
	DEBUG_BREAK( mpIB->Unlock() );

	mbIsLocked = false;
}

void nIndexBufferD3D9::activate()
{
	if ( mpIB && !mbIsLocked )
		mpRenderer->setIndexBuffer( (iIndexBuffer*)this );
}

}	// namespace graphics
}	// namespace inveria