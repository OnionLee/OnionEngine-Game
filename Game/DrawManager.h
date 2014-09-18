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

	//������ ����
	POINT m_pScreenSize;
	HWND hWnd;
	HINSTANCE hInst;
	//���̷�Ʈ ����
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPD3DXSPRITE			m_pd3dSprite;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);