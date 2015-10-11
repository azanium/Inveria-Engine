#ifndef _VERTEXINFOFACTORY_H_
#define _VERTEXINFOFACTORY_H_

#include "Buyut.h"
#include "Array.h"
#include "Structs.h"

#include <d3d9.h>

#define BUILD_USING_CG

#ifdef BUILD_USING_CG
#include <Cg/Cg.h>
#include <Cg/CgD3D9.h>
#endif

namespace inveria
{
namespace graphics
{

enum E_VDECL_USAGE_TYPE
{
	EVUT_DIRECT3D9	= 0,
#ifdef BUILD_USING_CG
	EVUT_CG,
	EVUT_DIRECT3D9_AND_CG,
#endif
	EVUT_MAX
};

// This class is dedicated for internal D3D and/or CG use for vertex stuffs like vertex declarations, etc.
class VertexInfoFactory: public Buyut
{
protected:
	D3DVERTEXELEMENT9**							mpVElement;
	core::Array< LPDIRECT3DVERTEXDECLARATION9 >	mpVDecl;
	LPDIRECT3DDEVICE9							mpD3DDevice;

#ifdef BUILD_USING_CG
	CGprogram									mpCGprogram;
#endif

public:
	VertexInfoFactory( LPDIRECT3DDEVICE9 pD3DDevice );
	~VertexInfoFactory();

#ifdef BUILD_USING_CG
	void	setCgProgram( CGprogram program );
#endif

	void	createVertexDeclaration( E_VDECL_USAGE_TYPE evutType, E_VERTEX_TYPE vertexType );
	
	// For EVUT_DIRECT3D9 only
	void				generateVertexDeclaration();
	void				setVertexDeclaration( E_VERTEX_TYPE vertexType );
	void				convertVertexFormat( E_VERTEX_TYPE vertexType, u32* outVertexFormat, u32* outVertexSize );
	D3DPRIMITIVETYPE	convertPrimitiveType( E_PRIMITIVE_TYPE primType );

protected:
	void	prepareVertexElements();
};

}	// namespace graphics
}	// namespace inveria

#endif	// _VERTEXINFOFACTORY_H_