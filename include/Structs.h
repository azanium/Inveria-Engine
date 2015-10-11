#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "Types.h"
#include "Vector.h"
#include "Color.h"
#include "Enums.h"

namespace inveria
{
namespace graphics
{

typedef struct SRenderConfig_s
{
	s32			width;
	s32			height;
	s32			depth;
	bool		fullscreen;
} SRenderConfig;

template < class T > inline E_VERTEX_TYPE getVertexType( T* ptr ) { return EVT_VERTEX_P; }
template < class T > inline u32 getVertexFormat( T* ptr ) { return 0; }

#define DEFINE_VERTEX( name, vertex_type, flags ) struct name; \
		template <> inline E_VERTEX_TYPE getVertexType( name* ptr ) { return vertex_type; } \
		template <> inline u32 getVertexFormat( name* ptr ) { return flags; } \
		struct name


DEFINE_VERTEX( SVertexP, EVT_VERTEX_P, EVF_XYZ )
{
	core::Vector3f pos;
};

DEFINE_VERTEX( SVertexPC, EVT_VERTEX_PC, EVF_XYZ | EVF_DIFFUSE )
{
	core::Vector3f pos;
	Color color;
};

DEFINE_VERTEX( SVertexPT, EVT_VERTEX_PT, EVF_XYZ | EVF_TEXCOUNT1 | EVF_TEX2D0 )
{
	core::Vector3f pos;
	core::Vector2f texCoord;
};

DEFINE_VERTEX( SVertexPTT, EVT_VERTEX_PTT,  EVF_XYZ | EVF_TEXCOUNT2 | EVF_TEX2D0 | EVF_TEX2D1 )
{
	core::Vector3f pos;
	core::Vector2f texCoord;
	core::Vector2f texCoord2;
};

DEFINE_VERTEX( SVertexPCT, EVT_VERTEX_PCT, EVF_XYZ | EVF_DIFFUSE | EVF_TEXCOUNT1 | EVF_TEX2D0 )
{
	core::Vector3f pos;
	Color color;
	core::Vector2f texCoord;
};

DEFINE_VERTEX( SVertexPN, EVT_VERTEX_PN, EVF_XYZ | EVF_NORMAL )
{
	core::Vector3f pos;
	core::Vector3f normal;
};

DEFINE_VERTEX( SVertexPNT, EVT_VERTEX_PNT, EVF_XYZ | EVF_NORMAL | EVF_TEXCOUNT1 | EVF_TEX2D0 )
{
	core::Vector2f pos;
	core::Vector3f normal;
	core::Vector2f texCoord;
};

DEFINE_VERTEX( SVertexPNTT, EVT_VERTEX_PNTT, EVF_XYZ | EVF_NORMAL | EVF_TEXCOUNT2 | EVF_TEX2D0 | EVF_TEX2D1 )
{
	core::Vector3f pos;
	core::Vector3f normal;
	core::Vector2f texCoord;
	core::Vector3f texCoord2;
};

DEFINE_VERTEX( SVertexPTTT, EVT_VERTEX_PTTT, EVF_XYZ | EVF_TEXCOUNT3 | EVF_TEX2D0 | EVF_TEX2D1 | EVF_TEX2D2 )
{
	core::Vector3f pos;
	core::Vector2f texCoord;
	core::Vector3f texCoord2;
	core::Vector3f texCoord3;
};

// Tangent Vertex for normal mapping and something like that, -Suhendra
DEFINE_VERTEX( SVertexPNTTGB, EVT_VERTEX_PNTTGB, EVF_XYZ | EVF_NORMAL | EVF_TEXCOUNT4 | EVF_TEX2D0 | EVF_TEX2D1 | EVF_TEX3D2 | EVF_TEX3D3 )
{
	core::Vector3f pos;
	core::Vector3f normal;
	core::Vector2f texCoord;
	core::Vector2f texCoord2;
	
	// Tangent Space Information
	core::Vector3f tangent;
	core::Vector3f biNormal;
	
	// We don't need the txb Vector, cos it is the same with the normal -Suhendra, but if you insist, here it is
	// core::Vector3f txb;
};

}	// namespace graphics
}	// namespace inveria

#endif	// _STRUCTS_H_
