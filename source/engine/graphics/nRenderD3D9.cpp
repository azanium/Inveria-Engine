#include "nRenderD3D9.h"
#include <stdio.h>

namespace inveria
{
namespace graphics
{

nRenderD3D9::nRenderD3D9( void* hWnd )
{
	mhWnd		 = static_cast< HWND >( hWnd );
	mbRunning	 = false;
	mbDeviceLost = false;

	mpCurrentVertexBuffer = 0;
	mpCurrentPrimitiveBuffer = 0;
}

nRenderD3D9::~nRenderD3D9()
{
	shutdown();
}

void nRenderD3D9::initialize( s32 width, s32 height, s32 depth, bool fullscreen, bool stencil, E_ANTIALIAS_SAMPLES antialias  )
{
	msRenderConfig.width		= width;
	msRenderConfig.height		= height;
	msRenderConfig.depth		= depth;
	msRenderConfig.fullscreen	= fullscreen;

	// Fix the incorrect rectangle area
	RECT rect;
	GetClientRect( mhWnd, &rect );
	
	if ( rect.right != width ) msRenderConfig.width = rect.right;
	if ( rect.bottom != height ) msRenderConfig.height = rect.bottom;

	if ( !initializeD3D9() ) return;

	// Initialize the vertex info factory
	mpVertexInfoFactory = new VertexInfoFactory( mpD3DDevice );
	// Generate the vertex declarations
	mpVertexInfoFactory->generateVertexDeclaration();

	setClearColor( Color( 0, 0, 0 ) );

	// Prepare for World Matrix, View Matrix, and Projection Matrix
	core::Matrix mat;
	mat.Identity();
	mWorldMatrix = mat;
	mViewMatrix = mat;

	// Set the frustum parameters  -Suhendra
	mfFOV = 45.0f;
	mfNearClippingPlane = 0.01f;
	mfFarClippingPlane = 1000.0f;

	mat.BuildPerspectiveProjectionMatrixLH( mfFOV, ( f32 )( msRenderConfig.width / msRenderConfig.height ), mfNearClippingPlane, mfFarClippingPlane );
	mProjectionMatrix = mat;


	prepareRenderStates();
}

void nRenderD3D9::shutdown()
{
	SAFE_THROW( mpVertexInfoFactory );

	releaseD3D9();
}

void nRenderD3D9::prepareRenderStates()
{
	setViewport( core::Recti( 0, 0, msRenderConfig.width, msRenderConfig.height ) );

	// Disable lighting
	mpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Set the default materials
	D3DMATERIAL9 mtrl;
	memset( &mtrl, 0, sizeof( D3DMATERIAL9 ) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	mpD3DDevice->SetMaterial( &mtrl );

	setTransform( ETT_WORLD, mWorldMatrix );
	setTransform( ETT_VIEW, mViewMatrix );
	setTransform( ETT_PROJECTION, mProjectionMatrix );
}

bool nRenderD3D9::initializeD3D9()
{
	mbRunning = false;

	mpD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if ( !mpD3D ) return false;

	if ( FAILED ( mpD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &mD3DDisplayMode ) ) )
	{
		return false;
	}

	// Fill up the Direct3D Present Parameter
	ZeroMemory( &mD3DPresentParameters, sizeof( D3DPRESENT_PARAMETERS ) );
	mD3DPresentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;	
	mD3DPresentParameters.Windowed					= msRenderConfig.fullscreen ? false : true;
	mD3DPresentParameters.BackBufferFormat			= mD3DDisplayMode.Format;
	mD3DPresentParameters.EnableAutoDepthStencil	= TRUE;
	mD3DPresentParameters.hDeviceWindow				= mhWnd;
	mD3DPresentParameters.BackBufferCount			= 1;

	// My TV Tuner overlay runs very slow caused by this flag :
	// m_d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE; 

	if ( msRenderConfig.fullscreen )
	{
		mD3DPresentParameters.BackBufferWidth				= msRenderConfig.width;
		mD3DPresentParameters.BackBufferHeight				= msRenderConfig.height;
		mD3DPresentParameters.BackBufferFormat				= D3DFMT_R5G6B5;
		mD3DPresentParameters.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;

		if ( msRenderConfig.depth == 32 && !mbStencil )
			mD3DPresentParameters.BackBufferFormat	= D3DFMT_A8R8G8B8;
	}

	// We use HAL only no pure software rendering
	D3DDEVTYPE	devType = D3DDEVTYPE_HAL;

	if ( meAntiAlias > EAS_NONE && meAntiAlias < EAS_MAX_SAMPLES )
	{
		DWORD qualityLevels = 0;

		if ( !FAILED( mpD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, devType, 
														 mD3DPresentParameters.BackBufferFormat, !msRenderConfig.fullscreen, 
														 ( D3DMULTISAMPLE_TYPE )meAntiAlias, &qualityLevels ) ) )
		{
			mD3DPresentParameters.MultiSampleQuality	= qualityLevels - 1;
			mD3DPresentParameters.MultiSampleType		= D3DMULTISAMPLE_2_SAMPLES;
			mD3DPresentParameters.SwapEffect			= D3DSWAPEFFECT_DISCARD;
		}
		else
		if ( !FAILED( mpD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, devType, 
														  mD3DPresentParameters.BackBufferFormat, !msRenderConfig.fullscreen, 
														  D3DMULTISAMPLE_NONMASKABLE, &qualityLevels ) ) )
		{
			mD3DPresentParameters.MultiSampleQuality	= qualityLevels-1;
			mD3DPresentParameters.MultiSampleType		= D3DMULTISAMPLE_NONMASKABLE;
			mD3DPresentParameters.SwapEffect			= D3DSWAPEFFECT_DISCARD;
		}
		else
		{
			meAntiAlias = EAS_NONE;
		}
	}

	if ( mbStencil )
	{
		// 8 bit of stencil buffer
		mD3DPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;

		if ( !FAILED( mpD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, devType,
												mD3DPresentParameters.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
												D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
		{
			if ( FAILED( mpD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, devType,
													    mD3DPresentParameters.BackBufferFormat,
													    mD3DPresentParameters.BackBufferFormat, D3DFMT_D24S8 ) ) )
			{
				mbStencil = false;
			}
		}
		else mbStencil = false;
	}

	// If we don't use the stencil choose 16 instead of D24S8
	if ( !mbStencil )
		mD3DPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;

	// We only create hardware vertex processing, never mind the other...
	if ( FAILED( mpD3D->CreateDevice( D3DADAPTER_DEFAULT, devType, mhWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3DPresentParameters,	&mpD3DDevice ) ) )
	{
		return false;
	}	// CreateDevice HARDWARE

	// Failed to create d3d9 device
	if ( !mpD3DDevice ) return false;

	if ( FAILED( mpD3DDevice->GetDeviceCaps( &mCaps ) ) ) return false;

	mnAnisotropicMax = mCaps.MaxAnisotropy;

	// Maximum texture in one pass
	mnTextureMax = mCaps.MaxSimultaneousTextures;

	if ( meAntiAlias > EAS_NONE && meAntiAlias < EAS_MAX_SAMPLES )
		mpD3DDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );

	if ( mbStencil &&
		 ( !( mCaps.StencilCaps & D3DSTENCILCAPS_INCRSAT )  ||
		   !( mCaps.StencilCaps & D3DSTENCILCAPS_DECRSAT )  ||
		   !( mCaps.StencilCaps & D3DSTENCILCAPS_KEEP ) ) )
	{
		mbStencil = false;
	}

	mbRunning = true;
	mbSceneRunning = false;

	return true;
}

void nRenderD3D9::releaseD3D9()
{
	SAFE_RELEASE( mpD3DDevice );
	SAFE_RELEASE( mpD3D );
}

bool nRenderD3D9::reset()
{
	releaseDefaultPoolResources();

	if ( FAILED( mpD3DDevice->Reset( &mD3DPresentParameters ) ) )
	{
		while ( mpD3DDevice->TestCooperativeLevel() == D3DERR_DEVICELOST )
			Sleep( 100 );

		if ( FAILED( mpD3DDevice->Reset( &mD3DPresentParameters) ) )
			return false;
	}

	reacquireDefaultPoolResources();

	prepareRenderStates();

	mbResetting = true;
	mbDeviceLost = false;

	return true;
}

bool nRenderD3D9::isResetting() const
{
	return mbDeviceLost;
}

bool nRenderD3D9::beginScene( bool clearColor , bool clearDepth , bool clearStencil )
{
	if ( !isRunning() ) return false;

	mbSceneRunning = false;
	mbResetting = false;
	
	if ( mbDeviceLost )
	{
		HRESULT hr;
		if ( FAILED( hr = mpD3DDevice->TestCooperativeLevel() ) )
		{
			if ( hr == D3DERR_DEVICELOST )
				return false;
			
			if ( hr == D3DERR_DEVICENOTRESET )
			{
				reset();
			}
			
			return false;
		}
	}

	DWORD flags = 0;
	if ( clearColor ) flags |= D3DCLEAR_TARGET;
	if ( clearDepth ) flags |= D3DCLEAR_ZBUFFER;
	if ( clearStencil ) flags |= D3DCLEAR_STENCIL;

	if ( FAILED( mpD3DDevice->Clear( 0, NULL, flags, mClearColor, 1.0f, 0 ) ) )
		return false;

	if ( FAILED( mpD3DDevice->BeginScene() ) )
		return false;

	mbSceneRunning = true;
	mbResetting = false;

	return true;
}

bool nRenderD3D9::endScene()
{	
	mbSceneRunning = false;

	if ( FAILED( mpD3DDevice->EndScene() ) )
		return false;

	HRESULT hr;

	hr = mpD3DDevice->Present( NULL, NULL, NULL, NULL );

	if ( hr == D3DERR_DEVICELOST )
	{
		mbDeviceLost = true;
	}
	else
	if ( FAILED( hr ) || hr == D3DERR_INVALIDCALL )
	{
		return false;
	}

	return true;
}

void nRenderD3D9::setClearColor( const Color& color )
{
	// Safer conversion rather than "mClearColor = color.getColor();"
	mClearColor = D3DCOLOR_COLORVALUE( color.getRedf(), color.getGreenf(), color.getBluef(), color.getAlphaf() );
}

void nRenderD3D9::setViewport( const core::Recti& viewRect )
{
	mViewport.X = viewRect.left;
	mViewport.Y = viewRect.top;
	mViewport.Width = viewRect.right;
	mViewport.Height = viewRect.bottom;
	mViewport.MinZ = 0.0f;
	mViewport.MaxZ = 1.0f;

	mpD3DDevice->SetViewport( &mViewport );
}

core::Recti nRenderD3D9::getViewport() const
{
	core::Recti r;
	r.left = mViewport.X;
	r.top = mViewport.Y;
	r.right = mViewport.Width;
	r.bottom = mViewport.Height;

	return r;
}

void nRenderD3D9::setTransform( E_TRANSFORM_TYPE transformType, const core::Matrix& matrix )
{
	switch ( transformType )
	{
	case ETT_WORLD:
		{
			mWorldMatrix = matrix;
			mpD3DDevice->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&mWorldMatrix );
		}
		break;

	case ETT_VIEW:
		{
			mViewMatrix = matrix;
			mpD3DDevice->SetTransform( D3DTS_VIEW, (D3DMATRIX*)&mViewMatrix );
		}
		break;

	case ETT_PROJECTION:
		{
			mProjectionMatrix = matrix;
			mpD3DDevice->SetTransform( D3DTS_PROJECTION, (D3DMATRIX*)&mProjectionMatrix );
		}
		break;
	}
}

core::Matrix nRenderD3D9::getTransform( E_TRANSFORM_TYPE transformType )
{
	switch ( transformType )
	{
	case ETT_WORLD:
		return mWorldMatrix;
		break;

	case ETT_VIEW:
		return mViewMatrix;
		break;

	case ETT_PROJECTION:
		return mProjectionMatrix;
		break;
	}

	// Stupid returner... do you have a better idea than this?
	// return *(( core::Matrix* )0);
	// Yeah, i got it, this way below is safer to return an identity matrix
	core::Matrix mat;
	mat.Identity();

	return mat;
}

iVertexBuffer* nRenderD3D9::createVertexBuffer( u32 numVerts, E_VERTEX_TYPE vertexType, E_BUFFER_TYPE bufferType )
{
	u32 usage = 0;
	D3DPOOL	pool;
	switch ( bufferType )
	{
	case EBT_STATIC_BUFFER:
		pool = D3DPOOL_MANAGED;
		break;

	case EBT_DYNAMIC_BUFFER:
		pool = D3DPOOL_DEFAULT;
		usage |= D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
		break;
	}

	u32 nVertexFormat;
	u32 nVertexSize;

	// exclusive function for Direct3D only
	mpVertexInfoFactory->convertVertexFormat( vertexType, &nVertexFormat, &nVertexSize );

	nVertexBufferD3D9* vertexBuffer = new nVertexBufferD3D9( this, numVerts, nVertexFormat, nVertexSize, vertexType, bufferType );

	if ( FAILED( mpD3DDevice->CreateVertexBuffer( nVertexSize * numVerts, usage, nVertexFormat, pool, &vertexBuffer->mpVB, NULL ) ) )
	{
		return 0;
	}
	
	// TODO: Vertex Buffer Manager need a storage list
	// Only D3DPOOL_DEFAULT got stored on the buffer manager which mean only EBT_DYNAMIC_BUFFER
	if ( bufferType == EBT_DYNAMIC_BUFFER )
	{
		mpDynamicVBList.push_back( vertexBuffer );
	}

	return vertexBuffer;
}

void nRenderD3D9::setVertexBuffer( iVertexBuffer* vertexBuffer )
{
	mpCurrentVertexBuffer = static_cast< nVertexBufferD3D9* >( vertexBuffer );

	if ( mpCurrentVertexBuffer->mpVB )
	{
		mpD3DDevice->SetStreamSource( 0, mpCurrentVertexBuffer->mpVB, 0, mpCurrentVertexBuffer->mnVertexSize );
		mpVertexInfoFactory->setVertexDeclaration( mpCurrentVertexBuffer->meVertexType );
	}

	// AhmadENGINE is using SetFVF and SetVertexDeclaration both... not wise though
	// Good Bye to Single Stream Obsolete vertex format ^_^		-Suhendra Ahmad
	// mpD3DDevice->SetFVF( mpCurrentVertexBuffer->mnVertexFormat );
}

iIndexBuffer* nRenderD3D9::createIndexBuffer( u32 numIndices, E_BUFFER_TYPE bufferType )
{
	u32 usage = 0;
	D3DPOOL pool;

	switch ( bufferType )
	{
	case EBT_STATIC_BUFFER:
		pool = D3DPOOL_MANAGED;
		usage |= D3DUSAGE_WRITEONLY;
		break;

	case EBT_DYNAMIC_BUFFER:
		pool = D3DPOOL_DEFAULT;

		// D3DPOOL_DEFAULT will suffer a severe performance without D3DUSAGE_WRITEONLY -Suhendra
		// Some stupid guy from GarageGames made wrong statement in this -Suhendra
		usage |= D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;	
		break;
	}

	nIndexBufferD3D9* indexBuffer = new nIndexBufferD3D9( this, numIndices, bufferType );

	if ( FAILED( mpD3DDevice->CreateIndexBuffer( sizeof( u16 ) * numIndices, usage, D3DFMT_INDEX16, pool, &indexBuffer->mpIB, 0  ) ) )
	{
		return 0;
	}

	if ( bufferType == EBT_DYNAMIC_BUFFER )
	{
		mpDynamicIBList.push_back( indexBuffer );
	}

	return indexBuffer;
}

void nRenderD3D9::setIndexBuffer( iIndexBuffer* indexBuffer )
{
	mpCurrentPrimitiveBuffer = static_cast< nIndexBufferD3D9* >( indexBuffer );

	if ( mpCurrentPrimitiveBuffer->mpIB )
	{
		mpD3DDevice->SetIndices( mpCurrentPrimitiveBuffer->mpIB );
	}
}

void nRenderD3D9::renderPrimitive( E_PRIMITIVE_TYPE primType, u32 startVertex, u32 primitiveCount )
{
	if ( mpCurrentVertexBuffer )
	{
		mpD3DDevice->DrawPrimitive( mpVertexInfoFactory->convertPrimitiveType( primType ), startVertex, primitiveCount );
	}
}

void nRenderD3D9::renderIndexedPrimitive( E_PRIMITIVE_TYPE primType, u32 minIndex, u32 startIndex, u32 primitiveCount )
{
	if ( mpCurrentVertexBuffer && mpCurrentPrimitiveBuffer )
	{
		mpD3DDevice->DrawIndexedPrimitive( mpVertexInfoFactory->convertPrimitiveType( primType ), 0, minIndex, mpCurrentVertexBuffer->mnNumVerts, startIndex, primitiveCount );
	}
}

void nRenderD3D9::renderIndexedPrimitiveImmediate( E_PRIMITIVE_TYPE primType, E_VERTEX_TYPE vertexType, u32 numVerts, u32 primitiveCount, const void* vertexData, const u16* indexData )
{
	mpVertexInfoFactory->setVertexDeclaration( vertexType );
	
	u32 vertexFormat, vertexSize;
	mpVertexInfoFactory->convertVertexFormat( vertexType, &vertexFormat, &vertexSize );
	mpD3DDevice->DrawIndexedPrimitiveUP( mpVertexInfoFactory->convertPrimitiveType( primType ), 0, numVerts, primitiveCount, indexData, D3DFMT_INDEX16, vertexData, vertexSize );
}

void nRenderD3D9::releaseDefaultPoolResources()
{
	for ( u32 i = 0; i < mpDynamicVBList.length(); i ++ )
	{
		nVertexBufferD3D9* vb = mpDynamicVBList[ i ];
		SAFE_RELEASE( vb->mpVB );
	}

	for ( u32 i = 0; i < mpDynamicIBList.length(); i ++ )
	{
		nIndexBufferD3D9* ib = mpDynamicIBList[ i ];
		SAFE_RELEASE( ib->mpIB );
	}

	mpCurrentVertexBuffer = 0;
	mpCurrentPrimitiveBuffer = 0;
}

void nRenderD3D9::reacquireDefaultPoolResources()
{
	for ( u32 i = 0; i < mpDynamicVBList.length(); i ++ )
	{
		nVertexBufferD3D9* vb = mpDynamicVBList[ i ];

		DEBUG_BREAK( FAILED( mpD3DDevice->CreateVertexBuffer( vb->mnNumVerts * vb->mnVertexSize, 
															  D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
															  vb->mnVertexFormat, D3DPOOL_DEFAULT, &vb->mpVB, NULL ) ) );
	}

	for ( u32 i = 0; i < mpDynamicIBList.length(); i ++ )
	{
		nIndexBufferD3D9* ib = mpDynamicIBList[ i ];

		DEBUG_BREAK( mpD3DDevice->CreateIndexBuffer( sizeof( u16 ) * ib->mnNumIndices, 
													 D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
													 D3DPOOL_DEFAULT, &ib->mpIB, NULL ) );
	}
}

}	// namespace graphics
}	// namespace inveria
