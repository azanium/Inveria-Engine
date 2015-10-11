#ifndef _ICANVAS_H_
#define _ICANVAS_H_

#include "Buyut.h"
#include "Types.h"

namespace inveria
{
namespace platform
{

class iCanvas: Buyut
{
public:
	iCanvas() {};
	virtual ~iCanvas() {};

	virtual void*	getHandle() = 0;
};

}	// namespace platform
}	// namespace inveria

#endif	// _ICANVAS_H_
