#ifndef _NCANVAS_H_
#define _NCANVAS_H_

#include "iCanvas.h"

namespace inveria
{
namespace platform
{

class nCanvas: public iCanvas
{
public:
	nCanvas( void* hwnd );
	~nCanvas();

	void*	getHandle() { return mhWnd; }

protected:
	void*	mhWnd;
};

}	// namespace platform
}	// namespace inveria

#endif	// _NCANVAS_H_
