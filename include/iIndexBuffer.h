#ifndef _IINDEXBUFFER_H_
#define _IINDEXBUFFER_H_

#include "Buyut.h"
#include "Enums.h"

namespace inveria
{
namespace graphics
{

class iIndexBuffer: public Buyut
{
public:
	iIndexBuffer() {};
	virtual ~iIndexBuffer() {};

	virtual bool			isValid() const = 0;
	virtual void*			lock( u32 startIndex = 0, u32 endIndex = 0 ) = 0;
	virtual void			unlock() = 0;
	virtual void			activate() = 0;
	virtual bool			isLocked() const = 0;
	virtual E_BUFFER_TYPE	getBufferType() const = 0;

	virtual E_DRIVER_TYPE	getDriverType() const = 0;
};


}	// namespace graphics
}	// namespace inveria

#endif	// _IINDEXBUFFER_H_