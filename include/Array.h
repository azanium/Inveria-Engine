#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "Types.h"

namespace inveria
{
namespace core
{

// This is the class for dynamic array used by the most of the managers of the engine
// Created by Suhendra Ahmad *_* on Monday, December 26th 2005 3:21pm
// Enhanced for C++ used, created on Friday, December 30th 2005 10:31pm
template <class T>
class Array
{
private:
	T*	m_pData;
	u32	mnUsed;
	u32	mnAllocated;
	u32	mnGrow;

	bool reallocate( u32 newsize )
	{
		T *data_old = m_pData;
		m_pData = new T[newsize];
		if (data_old)
		{
			u32 size = mnUsed > newsize ? newsize : mnUsed;
			for (u32 i=0; i<size; i++)
				m_pData[i] = data_old[i];
		}
		delete [] data_old;
		mnAllocated = newsize;
		return true;
	}

public:

	Array( void )
	{
		m_pData = NULL;
		mnUsed = 0;
		mnAllocated = 0;
		mnGrow = 20;
        reallocate(mnGrow);
	};

	Array( u32 size )
	{
		m_pData = NULL;
		mnUsed = 0;
		mnAllocated = 0;
		mnGrow = size;
        reallocate(mnGrow);
	};

	~Array( void )
	{
		if (m_pData) free(m_pData);
	};

	void operator=( Array<T> &other )
	{
		DEBUG_BREAK(!m_pData);

		if (m_pData) 
			delete [] m_pData;

		if (other.Allocated() == 0)
			m_pData = 0;
		else
		{
			m_pData = 0;
			mnAllocated = 0;
			reallocate(other.Allocated());
		}
		mnUsed = other.Length();

		for (u32 i=0; i<mnUsed; i++)
			m_pData[i] = other[i];
	};

	u32 push_back( const T &item )
	{
		DEBUG_BREAK(!m_pData);

		if (mnUsed+1 > mnAllocated)
		{
			reallocate(mnAllocated+mnGrow);
		}
		
		m_pData[mnUsed++] = item;
		return mnUsed-1;
	};

	u32 push_front( const T &item )
	{
		if (mnUsed+1 > mnAllocated)
			reallocate(mnAllocated+mnGrow);
		
		for (u32 i=0; i<mnUsed; i++)
			m_pData[i+1] = m_pData[i];

		mnUsed++;

		m_pData[0] = item;

		return 0;
	};

	void set_used( u32 size )
	{
		if ( mnAllocated < size )
			reallocate( size );

		mnUsed = size;
	};

	T& operator []( u32 index )
	{		
		DEBUG_BREAK(index>=mnUsed);
		
		return m_pData[index];
	};

	const T& operator []( u32 index ) const
	{		
		DEBUG_BREAK(index>=mnUsed);

		return m_pData[index];
	};

	u32 length( void ) const
	{
		return mnUsed;
	};

	u32 allocated( void ) const
	{
		return mnAllocated;
	};

	T*  pointer( void )
	{
		return T;
	};

	void erase( u32 index )
	{
		DEBUG_BREAK(index>=mnUsed);

		for (u32 i=index; i<mnUsed-1; i++)
			m_pData[i] = m_pData[i+1];
		mnUsed--;
	}

	void clear( void )
	{
		mnAllocated = 0;
		mnUsed = 0;
		
		if (m_pData) 
		{
			delete [] m_pData ;
			m_pData = 0;
		}
	};

	void release( void )
	{
		mnAllocated = 0;
		mnUsed = 0;
		if ( m_pData ) 
		{
			delete [] m_pData ;
			m_pData = 0;
		}
	}

	void setGrow( u32 size )
	{
		mnGrow = size;
	};

};

}	// namespace core
}	// namespace inveria

#endif	// _ARRAY_H_
