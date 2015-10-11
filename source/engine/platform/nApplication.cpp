#include "nApplication.h"
#include "nCanvas.h"

#include <windows.h>

namespace inveria
{
namespace platform
{

#define INVERIA_ENGINE_CLASS_NAME	"WickedWindowRule"

nApplication::nApplication()
{
	mpCanvas = 0;
}

nApplication::~nApplication()
{

}

void nApplication::onInit( InveriaEngine* engine )
{

}

void nApplication::onShutdown()
{

}

void nApplication::onUpdate()
{

}

void nApplication::onRender()
{

}

void nApplication::onEvent( const SAppEvent& event )
{

}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage( 0 );

	default:
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	return 0;
}

bool nApplication::run()
{
	MSG msg;

	bool result = true;

	if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
	{
		if ( msg.message == WM_QUIT ) result = false;

		TranslateMessage( &msg );
		DispatchMessage( &msg );

		onUpdate();
		onRender();
	}

	return result;
}

void nApplication::initCanvas( const c8* title, s32 width, s32 height, bool fullscreen )
{
	WNDCLASS wc;
	HINSTANCE hInstance = GetModuleHandle( 0 );

	ZeroMemory( &wc, sizeof( WNDCLASS ) );
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= 0;	//( HBRUSH )( COLOR_BTNFACE + 1 );
	wc.hCursor			= LoadCursor( 0, IDC_ARROW );
	wc.hIcon			= LoadIcon( 0, IDI_WINLOGO );
	wc.hInstance		= hInstance;
	wc.lpfnWndProc		= WndProc;
	wc.lpszClassName	= INVERIA_ENGINE_CLASS_NAME;
	wc.lpszMenuName		= NULL;
	wc.style			= CS_VREDRAW | CS_HREDRAW;

	if ( !RegisterClass( &wc ) ) return;

	RECT r;
	r.left		= 0;
	r.top		= 0;
	r.right		= width;
	r.bottom	= height;

	DWORD	style = WS_POPUP;
	if ( !fullscreen ) 
	{
		//style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
		style = WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	}


	AdjustWindowRect( &r, style, FALSE );

	u32 iWinWidth = r.right - r.left;
	u32 iWinHeight = r.bottom - r.top;

	// Put our window in the middle of the screen, it's wicked... ^_*
	u32 iPosLeft = ( GetSystemMetrics( SM_CXSCREEN ) - iWinWidth ) / 2;
	u32 iPosTop = ( GetSystemMetrics( SM_CYSCREEN ) - iWinHeight ) / 2;

	if ( fullscreen ) iPosLeft = iPosTop = 0;

	HWND hwnd = CreateWindow( INVERIA_ENGINE_CLASS_NAME, title, style, iPosLeft, iPosTop, iWinWidth, iWinHeight, NULL, NULL, hInstance, NULL );

	mpCanvas = new nCanvas( static_cast< void* >( hwnd ) );

}

}	// namespace platform
}	// namespace inveria
