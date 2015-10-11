#ifndef _NVERTEXBUFFERD3D9_H_
#define _NVERTEXBUFFERD3D9_H_

#include "iRenderer.h"
#include "iVertexBuffer.h"

#include <d3d9.h>

namespace inveria
{
namespace graphics
{

class nRenderD3D9;

class nVertexBufferD3D9: public iVertexBuffer
{
protected:
	friend class nRenderD3D9;

	LPDIRECT3DVERTEXBUFFER9	mpVB;
	void*					mpLockedPtr;
	bool					mbIsLocked;
	iRenderer*				mpRenderer;

	u32						mnNumVerts;
	u32						mnVertexFormat;
	u32						mnVertexSize;
	E_BUFFER_TYPE			meBufferType;
	E_VERTEX_TYPE			meVertexType;

public:
	nVertexBufferD3D9();
	nVertexBufferD3D9( iRenderer* renderer, u32 numVerts, u32 vertexFormat, u32 vertexSize, E_VERTEX_TYPE vertexType, E_BUFFER_TYPE bufferType );
	~nVertexBufferD3D9();

	LPDIRECT3DVERTEXBUFFER9 getVertexBufferD3D9() { return mpVB; }

	bool			isValid() const { return mpVB != NULL; }
	void*			lock( u32 startVertex, u32 endVertex );
	void			unlock();
	void			activate();
	bool			isLocked() const { return mbIsLocked; }
	E_BUFFER_TYPE	getBufferType() const { return meBufferType; }

	E_DRIVER_TYPE	getDriverType() const { return EDT_DIRECT3D9; }
};

}	// namespace graphics
}	// namespace inveria

#endif
