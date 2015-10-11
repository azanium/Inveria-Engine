#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#include "Buyut.h"
#include "Types.h"

#include <vector>
#include <algorithm>

namespace inveria
{
namespace core
{

//! Wrapper for STL pointer to avoid the use of STL inclusion all over the places :)
//! With this we can manage what we want with the list in one place
template < class T >
class ArrayList: public Buyut
{
public:
	ArrayList() {};

	ArrayList( ArrayList< T >& other )
	{
		duplicateFrom( other );
	}

	virtual ~ArrayList()
	{
		clear();
	};

	/**
	 * Add an element into the ArrayList
	 *
	 * @param element The element we want to add
	 */
	virtual	void add( T* element )
	{
		m_pElements.push_back( element );
	};

	/**
	 * Check whether the ArrayList is empty
	 */
	virtual bool empty() const
	{
		return m_pElements.empty();		
	};

	/**
	 * Get the number of elements exist on the ArrayList
	 */
	virtual	s32	size() const
	{
		return ( s32 )m_pElements.size();
	};

	/**
	 * Remove an element from the ArrayList
	 *
	 * @param element The element we want to remove
	 */
	virtual	void remove( T* element )
	{
		std::vector< T* >::iterator result;

		result = find( m_pElements.begin(), m_pElements.end(), element );

		if ( result != m_pElements.end() )
			m_pElements.erase( result );		
	};
	
	/**
	 * Get an element
	 *
	 * @param index The index the element we want to fetch
	 */
	virtual T*	get( s32 index )
	{
		return m_pElements[ index ];
	};

	/**
	 * Get an element
	 *
	 * @param index The index the element we want to fetch
	 */
	virtual T* operator []( s32 index )
	{
		return get( index );
	}

	/**
	 * Clear the ArrayList elements
	 */
	virtual void clear()
	{
		m_pElements.clear();
	};

	/**
	 * Check whether an element is contained in the ArrayList
	 *
	 * @param element The element we wanted to check
	 */
	virtual	bool contains( T* element )
	{
		std::vector< T* >::iterator result;

		result = find( m_pElements.begin(), m_pElements.end(), element );

		return ( result != m_pElements.end() );
	};

	/**
	 * Fetch the STL vector of the ArrayList
	 */
	virtual std::vector< T* > getSTLElements() 
	{ 
		return m_pElements; 
	}

	/**
	 * Duplicate another ArrayList into this ArrayList
	 *
	 * @param other The other ArrayList which is being copied from
	 */
	virtual void duplicateFrom( ArrayList< T >& other )
	{
		std::vector< T* > otherSTL = other.getSTLElements();
		std::vector< T* >::iterator it;

		for ( it = otherSTL.begin(); it != otherSTL.end(); it ++ )
			m_pElements.push_back( *it );
	};

protected:
	std::vector< T* >	m_pElements;
};

}	// namespace core
}	// namespace inveria

#endif	// _ARRAYLIST_H_
