#include "StdAfx.h"
#include "DrawManager.h"
#include "Resource.h"
#include "Director.h"


CDrawManager::CDrawManager(void)
{
	m_pScreenSize.x = 1280;
	m_pScreenSize.y = 1024;
}


CDrawManager::~CDrawManager(void)
{
}
void CDrawManager::init()
{
	initWindow();
	initDirectX();
}
void CDrawManager::initWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDI_GAME);
	wcex.lpszClassName	= "gungame";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);
#if _DEBUG
   hWnd = CreateWindow("gungame", "gungame", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, m_pScreenSize.x, m_pScreenSize.y, NULL, NULL, hInst, NULL);
#else
	hWnd = CreateWindow("gungame", "gungame", WS_POPUP,
     CW_USEDEFAULT, 0, m_pScreenSize.x, m_pScreenSize.y, NULL, NULL, hInst, NULL);
#endif
   if (!hWnd)
   {
      return;
   }

   ShowWindow(hWnd, 5);
   UpdateWindow(hWnd);
}
void CDrawManager::initDirectX()
{
	// Create the D3D object.
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return ;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
#if _DEBUG
    d3dpp.Windowed = TRUE;
#else 
	d3dpp.Windowed = FALSE;
#endif
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.BackBufferWidth = m_pScreenSize.x;
	d3dpp.BackBufferHeight = m_pScreenSize.y;
	d3dpp.BackBufferCount = 1;



    // Create the D3DDevice
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pd3dDevice ) ) )
    {
        return ;
    }

	//스프라이트 생성
	D3DXCreateSprite(m_pd3dDevice,&m_pd3dSprite);
}

void CDrawManager::drawBegin()
{
    // Clear the backbuffer to a black color
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255,0, 0, 255), 1.0f, 0 );

    m_pd3dDevice->BeginScene();
}

void CDrawManager::drawEnd()
{
    m_pd3dDevice->EndScene();


    m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	auto instance = GetModuleHandle(NULL);

	switch (message)
	{
	case WM_CREATE:
		CDIRECTOR->m_isActive = true;
		DialogBox(instance,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,DIGACTIVE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}