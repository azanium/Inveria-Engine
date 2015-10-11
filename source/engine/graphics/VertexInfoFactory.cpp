#include "VertexInfoFactory.h"
#include <stdio.h>

namespace inveria
{
namespace graphics
{

VertexInfoFactory::VertexInfoFactory( LPDIRECT3DDEVICE9 pD3DDevice ): mpD3DDevice( pD3DDevice )
{
#ifdef BUILD_USING_CG
	mpCGprogram = 0;
#endif

	LPDIRECT3DVERTEXDECLARATION9 vdecl = NULL;

	mpVElement = ( D3DVERTEXELEMENT9** )malloc( sizeof( D3DVERTEXELEMENT9* )*u32( EVT_VERTEX_MAX ) );

	for ( u32 i = 0; i < u32( EVT_VERTEX_MAX ); i ++ )
	{
		mpVDecl.push_back( vdecl );
		mpVElement[ i ] = 0;
	}

	prepareVertexElements();
}

VertexInfoFactory::~VertexInfoFactory()
{
	// Clear out our vertex declaration and vertex elements lists
	LPDIRECT3DVERTEXDECLARATION9 vdecl;
	for ( u32 i = 0; i < u32( EVT_VERTEX_MAX ); i ++ )
	{
		vdecl = mpVDecl[ i ];

		if ( vdecl )
			SAFE_RELEASE( vdecl );

		if ( mpVElement[ i ] )
			free( mpVElement[ i ] );
	}
	
	free( mpVElement );
	mpVDecl.clear();
}

void VertexInfoFactory::prepareVertexElements()
{
	D3DVERTEXELEMENT9* pVElement = NULL;
	u32 size = sizeof( D3DVERTEXELEMENT9 );

	for ( u32 i = 0; i < u32( EVT_VERTEX_MAX ); i ++ )
	{
		switch ( i )
		{
		case EVT_VERTEX_P:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					D3DDECL_END()
				};
				
				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*2 );
				memcpy( pVElement, vel, size*2 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PC:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*3 );
				memcpy( pVElement, vel, size*3 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*3 );
				memcpy( pVElement, vel, size*3 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PTT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
					D3DDECL_END()
				};			

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*4 );
				memcpy( pVElement, vel, size*4 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PCT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
					{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*4 );
				memcpy( pVElement, vel, size*4 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PN:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*3 );
				memcpy( pVElement, vel, size*3 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PNT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
					{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*4 );
				memcpy( pVElement, vel, size*4 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PNTT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
					{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					{ 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*5 );
				memcpy( pVElement, vel, size*5 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PTTT:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
					{ 0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*5 );
				memcpy( pVElement, vel, size*5 );
				mpVElement[ i ] = pVElement;
			}
			break;

		case EVT_VERTEX_PNTTGB:
			{
				D3DVERTEXELEMENT9 vel[] =
				{
					{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
					{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
					{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
					{ 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
					{ 0, 40, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
					{ 0, 52, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
					D3DDECL_END()
				};

				pVElement = ( D3DVERTEXELEMENT9* )malloc( size*7 );
				memcpy( pVElement, vel, size*7 );
				mpVElement[ i ] = pVElement;
			}
			break;
		}
	}
}

void VertexInfoFactory::createVertexDeclaration( E_VDECL_USAGE_TYPE evutType, E_VERTEX_TYPE vertexType )
{
	D3DVERTEXELEMENT9* velement = mpVElement[ u32( vertexType ) ];

	switch ( evutType )
	{
	case EVUT_CG:
		{
#ifdef BUILD_USING_CG
			cgD3D9ValidateVertexDeclaration( mpCGprogram, velement );

			// Clear out the CGprogram for next setCgProgram binding
			mpCGprogram = 0;
#endif
		} break;

	case EVUT_DIRECT3D9:
		{
			DEBUG_BREAK( mpD3DDevice->CreateVertexDeclaration( velement, &mpVDecl[ u32( vertexType ) ] ) );
		} break;

	case EVUT_DIRECT3D9_AND_CG:
		{
			DEBUG_BREAK( mpD3DDevice->CreateVertexDeclaration( velement, &mpVDecl[ u32( vertexType ) ] ) );

#ifdef BUILD_USING_CG
			cgD3D9ValidateVertexDeclaration( mpCGprogram, velement );
			
			// Clear out the CGprogram for next setCgProgram binding
			mpCGprogram = 0;
#endif

		} break;
	}
}

void VertexInfoFactory::generateVertexDeclaration()
{
	for ( u32 i = 0; i < u32( EVT_VERTEX_MAX ); i ++ )
	{
		if ( !mpVDecl[ i ] )
			SAFE_RELEASE( mpVDecl[ i ] );
		
		createVertexDeclaration( EVUT_DIRECT3D9, static_cast< E_VERTEX_TYPE >( i ) );
	}
}

void VertexInfoFactory::setVertexDeclaration( E_VERTEX_TYPE vertexType )
{
	if ( vertexType == EVT_VERTEX_MAX )
	{
		mpD3DDevice->SetVertexDeclaration( NULL );
	}

	u32 index = u32( vertexType );
	mpD3DDevice->SetVertexDeclaration( mpVDecl[ index ] );
}

void VertexInfoFactory::convertVertexFormat( E_VERTEX_TYPE vertexType, u32* outVertexFormat, u32* outVertexSize )
{
	u32 vertexFormat = 0;
	u32 vertexSize = 0;

	switch ( vertexType )
	{
	case EVT_VERTEX_P:
		vertexFormat = getVertexFormat( ( SVertexP* ) NULL );
		vertexSize = sizeof( SVertexP );
		break;

	case EVT_VERTEX_PC:
		vertexFormat = getVertexFormat( ( SVertexPC* ) NULL );
		vertexSize = sizeof( SVertexPC );
		break;

	case EVT_VERTEX_PT:
		vertexFormat = getVertexFormat( ( SVertexPT* ) NULL );
		vertexSize = sizeof( SVertexPT );
		break;

	case EVT_VERTEX_PTT:
		vertexFormat = getVertexFormat( ( SVertexPTT* ) NULL );
		vertexSize = sizeof( SVertexPTT );
		break;

	case EVT_VERTEX_PCT:
		vertexFormat = getVertexFormat( ( SVertexPCT* ) NULL );
		vertexSize = sizeof( SVertexPCT );
		break;

	case EVT_VERTEX_PN:
		vertexFormat = getVertexFormat( ( SVertexPN* ) NULL );
		vertexSize = sizeof( SVertexPN );
		break;

	case EVT_VERTEX_PNT:
		vertexFormat = getVertexFormat( ( SVertexPNT* ) NULL );
		vertexSize = sizeof( SVertexPNT );
		break;

	case EVT_VERTEX_PNTT:
		vertexFormat = getVertexFormat( ( SVertexPNTT* ) NULL );
		vertexSize = sizeof( SVertexPNTT );
		break;

	case EVT_VERTEX_PTTT:
		vertexFormat = getVertexFormat( ( SVertexPTTT* ) NULL );
		vertexSize = sizeof( SVertexPTTT );
		break;

	case EVT_VERTEX_PNTTGB:
		vertexFormat = getVertexFormat( ( SVertexPNTTGB* ) NULL );
		vertexSize = sizeof( SVertexPNTTGB );
		break;
	}

	*outVertexFormat = vertexFormat;
	*outVertexSize = vertexSize;
}

D3DPRIMITIVETYPE VertexInfoFactory::convertPrimitiveType( E_PRIMITIVE_TYPE primType )
{
	switch ( primType )
	{
	case EPT_POINTLIST:
		return D3DPT_POINTLIST;
		break;

	case EPT_LINELIST:
		return D3DPT_LINELIST;
		break;

	case EPT_LINESTRIP:
		return D3DPT_LINESTRIP;
		break;

	case EPT_TRIANGLELIST:
		return D3DPT_TRIANGLELIST;
		break;

	case EPT_TRIANGLESTRIP:
		return D3DPT_TRIANGLESTRIP;
		break;

	case EPT_TRIANGLEFAN:
		return D3DPT_TRIANGLEFAN;
		break;
	}

	return D3DPT_POINTLIST;
}

#ifdef BUILD_USING_CG

void VertexInfoFactory::setCgProgram( CGprogram program )
{
	mpCGprogram = program;
}

#endif



}	// namespace graphics
}	// namespace inveria