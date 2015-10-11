#ifndef _IAPPLICATION_H_
#define _IAPPLICATION_H_

#include "Buyut.h"
#include "Types.h"
#include "Vector.h"
#include "iCanvas.h"

namespace inveria
{

class InveriaEngine;

namespace platform
{

enum E_APPEVENT_TYPE
{
	EAT_NONE			= 0,
	EAT_KEYDOWN,
	EAT_KEYUP,
	EAT_KEYPRESS,
	EAT_MOUSEMOVE,
	EAT_MOUSEDOWN,
	EAT_MOUSEUP,
	EAT_APP_TERMINTATE,
	EAT_MAX
};

struct SMouseEvent
{
	core::Vector2f pos;
	core::Vector2f delta;
	s32 button;
};

struct SKeyboard
{
	s32	keyID;
};

struct SAppEvent
{
	E_APPEVENT_TYPE	type;
	SMouseEvent		mouse;
	SKeyboard		keyboard;
};

class iApplication: public Buyut
{
public:
	iApplication() {};
	virtual ~iApplication() {};

	virtual void		onInit( InveriaEngine* engine ) = 0;
	virtual void		onShutdown() = 0;

	virtual void		onUpdate() = 0;
	virtual void		onRender() = 0;

	virtual void		onEvent( const SAppEvent& event ) = 0;
	virtual bool		run() = 0;

	virtual iCanvas*	getCanvas() = 0;
};

}	// namespace platform
}	// namespace inveria

#endif	// _IAPPLICATION_H_
