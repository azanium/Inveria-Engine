#ifndef _IRENDERER_H_
#define _IRENDERER_H_

#include "Buyut.h"
#include "Types.h"
#include "Enums.h"
#include "Structs.h"
#include "Color.h"
#include "Matrix.h"
#include "Rect.h"
#include "iVertexBuffer.h"
#include "iIndexBuffer.h"

namespace inveria
{
namespace graphics
{

class iRenderer: public Buyut
{
public:
	iRenderer() {};
	virtual ~iRenderer() {};

	virtual bool			reset() = 0;
	virtual bool			isResetting() const = 0;
	virtual bool			beginScene( bool clearColor = true, bool clearDepth = true, bool clearStencil = false ) = 0;
	virtual bool			endScene() = 0;
	virtual E_DRIVER_TYPE	getDriverType() const = 0;
	virtual SRenderConfig&	getConfiguration() = 0;
	virtual bool			isRunning() const = 0;
	virtual bool			isSceneRunning() const = 0;
	virtual void			setClearColor( const Color& color ) = 0;
	virtual void			setViewport( const core::Recti& viewRect ) = 0;
	virtual core::Recti		getViewport() const = 0;
	virtual void			setTransform( E_TRANSFORM_TYPE transformType, const core::Matrix& matrix ) = 0;
	virtual	void			setFOV( f32 fovDegree ) = 0;
	virtual f32				getFOV() const = 0;
	virtual void			setClippingPlane( f32 nearPlane, f32 farPlane ) = 0;
	virtual void			getClippingPlane( f32* nearPlane, f32* farPlane ) = 0;
	virtual void			renderPrimitive( E_PRIMITIVE_TYPE primType, u32 startVertex, u32 primitiveCount ) = 0;
	virtual void			renderIndexedPrimitive( E_PRIMITIVE_TYPE primType, u32 minIndex, u32 startIndex, u32 primitiveCount ) = 0;
	virtual void			renderIndexedPrimitiveImmediate( E_PRIMITIVE_TYPE primType, E_VERTEX_TYPE vertexType, u32 numVerts, u32 primitiveCount, const void* vertexData, const u16* indexData ) = 0;

	
	// vertex buffer & primitive buffer
	virtual iVertexBuffer*	createVertexBuffer( u32 numVerts, E_VERTEX_TYPE vertexType, E_BUFFER_TYPE bufferType ) = 0;
	virtual void			setVertexBuffer( iVertexBuffer* vertexBuffer ) = 0;
	virtual iIndexBuffer*	createIndexBuffer( u32 numIndices, E_BUFFER_TYPE bufferType ) = 0;
	virtual	void			setIndexBuffer( iIndexBuffer* indexBuffer ) = 0;
};

}	// namespace graphics
}	// namespace inveria

#endif
