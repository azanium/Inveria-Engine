#ifndef _INVERIA_H_
#define _INVERIA_H_

#include "Buyut.h"
#include "Types.h"
#include "iRenderer.h"
#include "iApplication.h"
#include "Array.h"
#include "Dimension.h"
#include "Enums.h"
#include "Structs.h"
#include "Matrix.h"
#include "Rect.h"
#include "Vector.h"
#include "iVertexBuffer.h"
#include "iIndexBuffer.h"
#include "Primitive.h"
#include "iCanvas.h"

#ifdef INVERIA_EXPORTS
#define INVERIA_API __declspec( dllexport )
#else
#define INVERIA_API __declspec( dllimport )
#endif

namespace inveria
{

class InveriaEngine: public Buyut
{
public:
	InveriaEngine() {};
	~InveriaEngine() {};

	virtual void					shutdown() = 0;
	virtual platform::iApplication* getApplication() = 0;
	virtual graphics::iRenderer*	getRenderer() = 0;
	
	virtual bool isOnline() const = 0;
	virtual bool run() = 0;
};

}	// namespace inveria

extern "C"
{

INVERIA_API inveria::InveriaEngine* createInveriaEngine( inveria::graphics::E_DRIVER_TYPE driverType,
														 const c8* canvasTitle,
														 s32 canvasWidth, s32 canvasHeight, s32 depth = 32,
														 bool fullscreen = false, bool stencil = true,
														 inveria::graphics::E_ANTIALIAS_SAMPLES antiAlias = inveria::graphics::EAS_NONE );
}

#endif	// _INVERIA_H_
