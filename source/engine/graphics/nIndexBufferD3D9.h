#ifndef _NPRIMITIVEBUFFERD3D9_H_
#define _NPRIMITIVEBUFFERD3D9_H_

#include "iIndexBuffer.h"
#include "iRenderer.h"

#include <d3d9.h>

namespace inveria
{
namespace graphics
{

class nRenderD3D9;

class nIndexBufferD3D9: public iIndexBuffer
{
friend class nRenderD3D9;

protected:
	LPDIRECT3DINDEXBUFFER9	mpIB;
	iRenderer*				mpRenderer;
	bool					mbIsLocked;
	void*					mpLockedPtr;
	E_BUFFER_TYPE			meBufferType;
	u32						mnNumIndices;

public:
	nIndexBufferD3D9() {};
	nIndexBufferD3D9( iRenderer* renderer, u32 numIndices, E_BUFFER_TYPE bufferType );
	~nIndexBufferD3D9();

	bool			isValid() const { return mpIB != NULL; }
	void*			lock( u32 startIndex, u32 endIndex );
	void			unlock();
	void			activate();
	bool			isLocked() const { return mbIsLocked; }
	E_BUFFER_TYPE	getBufferType() const { return meBufferType; }

	E_DRIVER_TYPE	getDriverType() const { return EDT_DIRECT3D9; }
};

}	// namespace graphics
}	// namespace inveria

#endif	// _NPRIMITIVEBUFFERD3D9_H_