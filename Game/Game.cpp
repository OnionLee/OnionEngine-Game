// gungame.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "Director.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
#if _DEBUG
	FILE * fp;

	AllocConsole();
	freopen_s(&fp, "CONIN$", "rb", stdin);
	freopen_s(&fp, "CONOUT$", "wb", stdout);
#endif
	CDIRECTOR->Init();
	CDIRECTOR->Loop();
	CDIRECTOR->Release();

	return 0;
}