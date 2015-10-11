#ifndef _NRENDERD3D9_H_
#define _NRENDERD3D9_H_

#include "iRenderer.h"
#include "nVertexBufferD3D9.h"
#include "nIndexBufferD3D9.h"
#include "VertexInfoFactory.h"
#include "Array.h"

#include <d3d9.h>
#include <d3dx9.h>

namespace inveria
{
namespace graphics
{

class nRenderD3D9: public iRenderer
{
public:
	nRenderD3D9() {};
	nRenderD3D9( void* hWnd );
	~nRenderD3D9();

	// Internal D3D9 Renderer API calls
	void				initialize( s32 width, s32 height, s32 depth, bool fullscreen, bool stencil, E_ANTIALIAS_SAMPLES antialias  );
	void				shutdown();
	LPDIRECT3DDEVICE9	getD3D9Device() { return mpD3DDevice; }
	
	// User-Visible Renderer API calls
	bool				reset();
	bool				isResetting() const;
	bool				beginScene( bool clearColor /* = true */, bool clearDepth /* = true */, bool clearStencil /* = false  */ );
	bool				endScene();
	E_DRIVER_TYPE		getDriverType() const { return EDT_DIRECT3D9; }
	SRenderConfig&		getConfiguration() { return msRenderConfig; }
	bool				isRunning() const { return mbRunning; }
	bool				isSceneRunning() const { return mbSceneRunning; }
	void				setClearColor( const Color& color );
	void				setViewport( const core::Recti& viewRect );
	core::Recti			getViewport() const;
	void				setTransform( E_TRANSFORM_TYPE transformType, const core::Matrix& matrix );
	core::Matrix		getTransform( E_TRANSFORM_TYPE transformType );
	void				setFOV( f32 fovDegree ) { mfFOV = fovDegree; }
	f32					getFOV() const { return mfFOV; }
	void				setClippingPlane( f32 nearPlane, f32 farPlane ) { mfNearClippingPlane = nearPlane; mfFarClippingPlane = farPlane; }
	void				getClippingPlane( f32* nearPlane, f32* farPlane ) { *nearPlane = mfNearClippingPlane; *farPlane = mfFarClippingPlane; }
	void				renderPrimitive( E_PRIMITIVE_TYPE primType, u32 startVertex, u32 primitiveCount );
	void				renderIndexedPrimitive( E_PRIMITIVE_TYPE primType, u32 minIndex, u32 startIndex, u32 primitiveCount );
	void				renderIndexedPrimitiveImmediate( E_PRIMITIVE_TYPE primType, E_VERTEX_TYPE vertexType, u32 numVerts, u32 primitiveCount, const void* vertexData, const u16* indexData );

	// Vertex Buffer
	iVertexBuffer*		createVertexBuffer( u32 numVerts, E_VERTEX_TYPE vertexType, E_BUFFER_TYPE bufferType );
	void				setVertexBuffer( iVertexBuffer* vertexBuffer );
	iIndexBuffer*		createIndexBuffer( u32 numIndices, E_BUFFER_TYPE bufferType );
	void				setIndexBuffer( iIndexBuffer* indexBuffer );

protected:	// Renderer internal API calls here
	bool			initializeD3D9();
	void			releaseD3D9();
	void			prepareRenderStates();
	void			releaseDefaultPoolResources();
	void			reacquireDefaultPoolResources();

protected:	// Renderer related variables here
	SRenderConfig			msRenderConfig;
	bool					mbStencil;
	E_ANTIALIAS_SAMPLES		meAntiAlias;
	bool					mbRunning;
	bool					mbSceneRunning;
	bool					mbResetting;
	l32						mnAnisotropicMax;
	u32						mnTextureMax;
	bool					mbDeviceLost;
	core::Matrix			mWorldMatrix;
	core::Matrix			mViewMatrix;
	core::Matrix			mProjectionMatrix;
	f32						mfFOV;
	f32						mfNearClippingPlane;
	f32						mfFarClippingPlane;
	nVertexBufferD3D9*		mpCurrentVertexBuffer;
	nIndexBufferD3D9*		mpCurrentPrimitiveBuffer;
	VertexInfoFactory*		mpVertexInfoFactory;
	
	core::Array< nVertexBufferD3D9* >	mpDynamicVBList;
	core::Array< nIndexBufferD3D9* >	mpDynamicIBList;

protected:	// D3D9 related variables here
	LPDIRECT3D9				mpD3D;
	LPDIRECT3DDEVICE9		mpD3DDevice;
	D3DDISPLAYMODE			mD3DDisplayMode;
	D3DPRESENT_PARAMETERS	mD3DPresentParameters;
	D3DCAPS9				mCaps;
	HWND					mhWnd;
	D3DCOLOR				mClearColor;
	D3DVIEWPORT9			mViewport;
};

}	// namespace graphics
}	// namespace inveria

#endif	// _NRENDERD3D9_H_
