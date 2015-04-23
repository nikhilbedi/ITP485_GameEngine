

//--------------------------------------------------------------------------------------
// File: Tutorial02.cpp
//
// This application displays a triangle using Direct3D 11
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729719.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <PrecompiledHeader.h>

#include "../../resource.h"
#include <InputLayoutCache.h>
#include <AppManager.h>
#include <MeshManager.h>


using namespace ITP485;




//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = nullptr;
HWND                    g_hWnd = nullptr;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );



//move to the executable directory and then the Data folder
void SetWorkingDirectory()
{
	wchar_t path[ 4096 ];
	GetModuleFileName( nullptr, path, 4096 );
	//find the second to last \ and remove it
	int length = lstrlen( path );
	int componentsFound = 0;
	for( int i = length - 1; i >= 0; --i )
	{
		if( path[ i ] == '\\' )
		{
			if( ++componentsFound == 2 )
			{
				//okay, the end is right after i...
				path[ i ] = '\0';
				break;
			}
		}
	}
	lstrcat( path, L"\\Data" );
	bool didSucceed = SetCurrentDirectory( path ) != 0;
	Dbg_Assert( didSucceed, "Problem Setting Working Directory" );
}

void InitSubSystems()
{
	SetWorkingDirectory();

	GraphicsDriver::StaticInit( g_hWnd );

	//todo: add any init code here
	MeshComponentPool::Get().StartUp();
	KeyFramePool::Get().StartUp();
}

void RunLoop()
{
	AppManager appManager;
	appManager.Init();

	//run our main game loop!
	appManager.RunGameLoop();
}

void ShutdownSubSystems()
{
	//todo add any shutdown code here in the right order...
	MeshManager::Get().Clear();
	InputLayoutCache::Get().Clear();
	GraphicsDriver::StaticDestroy();

	MeshComponentPool::Get().ShutDown();

}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

	if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
	{
		return 0;
	}

	InitSubSystems();

	RunLoop();

	DestroyWindow( g_hWnd );

	ShutdownSubSystems();

	return 0;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"ITP485WindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"ITP485WindowClass", L"ITP485 Engine",
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                           nullptr );
	if( !g_hWnd )
	{
		return E_FAIL;
	}

    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}




//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM inWParam, LPARAM inLParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;
			
		case WM_KEYDOWN:
			if( ( inLParam & ( 1 << 30 ) ) == 0 )
			{
				//great, it just went down!
				InputManager::Get().OnKeyEvent( EIA_KeyDown, inWParam );
			}
			break;
			
        default:
			return DefWindowProc( hWnd, message, inWParam, inLParam );
    }

    return 0;
}


