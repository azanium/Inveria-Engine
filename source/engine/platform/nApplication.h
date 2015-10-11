#ifndef _NAPPLICATION_H_
#define _NAPPLICATION_H_

#include "iApplication.h"

namespace inveria
{
namespace platform
{

class nApplication: public iApplication
{
public:
	nApplication();
	~nApplication();

	virtual void		onInit( InveriaEngine* engine );
	virtual void		onShutdown();

	virtual void		onUpdate();
	virtual void		onRender();

	virtual void		onEvent( const SAppEvent& event );
	virtual bool		run();

	virtual iCanvas*	getCanvas() { return mpCanvas; }

	virtual void		initCanvas( const c8* title, s32 width, s32 height, bool fullscreen );

protected:
	iCanvas*	mpCanvas;

};
	
}	// namespace platform
}	// namespace inveria

#endif	// _IAPPLICATION_H_
