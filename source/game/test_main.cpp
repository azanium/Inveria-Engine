
#include "Inveria.h"
#include <stdio.h>
#include <stdlib.h>

using namespace inveria;
using namespace inveria::core;
using namespace inveria::graphics;


int main( int argc, char *argv[] )
{
	InveriaEngine* engine = createInveriaEngine( EDT_DIRECT3D9, "Inveria Engine", 800, 600, 32, false, false, EAS_2_SAMPLES );

	iRenderer* render = engine->getRenderer();
	render->setClearColor( Color( 200, 200, 200 ) );

	SVertexPC vpc[3];
	vpc[0].pos = Vector3f( 0.0f, 0.0f, 5.0f );
	vpc[0].color = Color( 255, 0, 0 );
	vpc[1].pos = Vector3f( 1.0f, 0.0f, 5.0f );
	vpc[1].color = Color( 0, 255, 0 );
	vpc[2].pos = Vector3f( 0.0f, -1.0f, 5.0f );
	vpc[2].color = Color( 0, 0, 255 );

	u16 indices[3] = { 0, 1, 2 };

	Primitive< SVertexPC > primitive( render, 3, 3, EBT_DYNAMIC_BUFFER );
	//primitive.copyVBFromArray( vpc, 3 );
	//primitive.copyIBFromArray( indices, 3 );

/*
	vpc[0].pos = Vector3f( -1.0f, 1.0f, 5.0f );
	vpc[0].color = Color( 255, 0, 0 );
	vpc[1].pos = Vector3f( 0.0f, 1.0f, 5.0f );
	vpc[1].color = Color( 0, 255, 0 );
	vpc[2].pos = Vector3f( 0.0f, 0.0f, 5.0f );
	vpc[2].color = Color( 0, 0, 255 );

	Primitive< SVertexPC > primitive2( render, 3, 3, EBT_DYNAMIC_BUFFER );
	primitive2.copyVBFromArray( vpc, 3 );
	primitive2.copyIBFromArray( indices, 3 );
*/

	while ( engine->run() )
	{
		if ( render->beginScene( true, true, false ) )
		{
			if ( !render->isResetting() )
			{
			//	primitive.copyVBFromArray( vpc, 3 );
			//	primitive.copyIBFromArray( indices, 3 );
			}

			//primitive.activate();
			//render->renderIndexedPrimitive( EPT_TRIANGLELIST, 0, 0, 1 );
			render->renderIndexedPrimitiveImmediate( EPT_TRIANGLELIST, EVT_VERTEX_PC, 3, 1, vpc, indices );

			render->endScene();
		}
	}

	engine->shutdown();

	return 0;
}
