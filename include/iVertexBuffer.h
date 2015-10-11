#ifndef _IVERTEXBUFFER_H_
#define _IVERTEXBUFFER_H_

#include "Buyut.h"
#include "Enums.h"

namespace inveria
{
namespace graphics
{

class iVertexBuffer: public Buyut
{
public:
	iVertexBuffer() {};
	virtual ~iVertexBuffer() {};

	virtual bool			isValid() const = 0;
	virtual void*			lock( u32 startVertex = 0, u32 endVertex = 0 ) = 0;
	virtual void			unlock() = 0;
	virtual void			activate() = 0;
	virtual bool			isLocked() const = 0;
	virtual E_BUFFER_TYPE	getBufferType() const = 0;

	virtual E_DRIVER_TYPE getDriverType() const = 0;
};


}	// namespace graphics
}	// namespace inveria

#endif	// _IVERTEXBUFFER_H_
