#pragma once
class CDrawManager
{
public:
	CDrawManager(void);
	~CDrawManager(void);

	void init();
	void initWindow();
	void initDirectX();
	
	void drawBegin();
	void drawEnd();

	//윈도우 과련
	POINT m_pScreenSize;
	HWND hWnd;
	HINSTANCE hInst;
	//다이렉트 관련
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPD3DXSPRITE			m_pd3dSprite;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);