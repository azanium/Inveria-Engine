
#ifndef _BUYUT_H_
#define _BUYUT_H_

#include "Types.h"

/********************************************************
   This is the ancestor of the classes on 
   the Cross Engine.
   
   Buyut in Sundanese mean the great ancestor,
   and Cicit in Sundanese mean the descendant.
   Sorry, for the language, but i'm not a sundanese,
   i'm a batavian (betawi). I use sundanese
   to respect the city where i live, Bandung.
  
   Cut the crap, i'll show you the usage:
   ========================================
   
   If you want to create an object and delete
   it, you use it like this:
  
   class B;	// class B: public(IBuyut)
   B *pB = createB;
  
   pB->Throw();
  
   Suhendra Ahmad on Thu, November 23rd 2006 9:46AM
  *******************************************************/

namespace inveria
{

class Buyut
{
public:
	
	Buyut(): m_nCicit(1) {}

	virtual ~Buyut() {}

	void Catch()
	{
		++m_nCicit;
	}

	bool Throw()
	{
		if (m_nCicit<=0) __asm int 3;
		--m_nCicit;

		if (!m_nCicit)
		{
			delete this;
			return true;
		}

		return false;
	}

private:
	i32		m_nCicit;
};

#ifndef SAFE_THROW
#define SAFE_THROW(p) { if (p) { (p)->Throw(); p = NULL; }; }
#endif

}	// namespace inveria

#endif	// _IBUYUT_H_
