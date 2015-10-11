#include "engine/nInveria.h"
#include "graphics/nRenderD3D9.h"
#include "platform/nApplication.h"

namespace inveria
{

nInveria::nInveria()
{
	mpApplication = 0;
	mpRenderer = 0;
	mbOnline = false;
}

nInveria::~nInveria()
{
	shutdown();
}

void nInveria::shutdown()
{
	if ( mpApplication )
		SAFE_THROW( mpApplication );

	if ( mpRenderer )
		SAFE_THROW( mpRenderer );
}

bool nInveria::run()
{
	return mpApplication->run();	
}

void nInveria::initialize( graphics::E_DRIVER_TYPE driverType,
						   const c8* canvasTitle,
						   s32 canvasWidth, s32 canvasHeight, s32 depth,
						   bool fullscreen, bool stencil,
						   graphics::E_ANTIALIAS_SAMPLES antiAlias )
{
	if ( isOnline() ) shutdown();

	mbOnline = true;

	platform::nApplication* app = new platform::nApplication();
	app->initCanvas( canvasTitle, canvasWidth, canvasHeight, fullscreen );
	platform::iCanvas* canvas = app->getCanvas();
	mpApplication = app;

	if ( !mpApplication ) mbOnline = false;

	if	( driverType == graphics::EDT_DIRECT3D9 )
	{
		graphics::nRenderD3D9* render = new graphics::nRenderD3D9( canvas->getHandle() );
		render->initialize( canvasWidth, canvasHeight, depth, fullscreen, stencil, antiAlias );
		mpRenderer = render;
	}

	mpApplication->onInit( this );
}

void nInveria::release()
{
	mpApplication->onShutdown();

	SAFE_THROW( mpApplication );
}

}	// namespace inveria

extern "C"
{

INVERIA_API
inveria::InveriaEngine* createInveriaEngine( inveria::graphics::E_DRIVER_TYPE driverType,
											 const c8* canvasTitle,
											 s32 canvasWidth, s32 canvasHeight, s32 depth,
											 bool fullscreen, bool stencil,
											 inveria::graphics::E_ANTIALIAS_SAMPLES antiAlias )
{
	inveria::nInveria* pInveria = new inveria::nInveria();
	pInveria->initialize( driverType, canvasTitle, canvasWidth, canvasHeight, depth, fullscreen, stencil, antiAlias );

	return pInveria;
}

}
