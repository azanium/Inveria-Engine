#ifndef _NINVERIA_H_
#define _NINVERIA_H_

#include "Inveria.h"

namespace inveria
{

class nInveria: public InveriaEngine
{
public:
	nInveria();
	~nInveria();

	void					shutdown();
	platform::iApplication* getApplication() { return mpApplication; }
	graphics::iRenderer*	getRenderer() { return mpRenderer; }
	
	bool	isOnline() const { return mbOnline; }
	bool	run();

	void	initialize( graphics::E_DRIVER_TYPE driverType,
						const c8* canvasTitle,
						s32 canvasWidth, s32 canvasHeight, s32 depth,
						bool fullscreen, bool stencil,
						graphics::E_ANTIALIAS_SAMPLES antiAlias );
	void	release();

protected:
	bool					mbOnline;

	platform::iApplication*	mpApplication;
	graphics::iRenderer*	mpRenderer;
};

}	// namespace Inveria

#endif	// _NINVERIA_H_
