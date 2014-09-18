#include "StdAfx.h"
#include "Director.h"


CDirector::CDirector(void)
{
	m_isActive = false;
}


CDirector::~CDirector(void)
{
}

void CDirector::Init()
{
	
	m_pDrawManager = new CDrawManager();
	m_pSceneManager = new CSceneManager();
	m_pInputManager = new CInputManager();
	m_pSoundManager= new CSoundManager();
	m_pTimeManager = new CTimeManager();
	m_pDataManager = new CDataManager();
	m_pTextureManager = new CTextureManager();

	m_pTimeManager->init();
	m_pDrawManager->init();
	m_pInputManager->init();
	m_pSceneManager->init();
	m_pDataManager->init();

}
void CDirector::Loop()
{
	// TODO: 여기에 코드를 입력합니다.
	MSG msg;

	// 기본 메시지 루프입니다.
	while (1)
	{
		if(PeekMessage(&msg,0,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,0,0,0))
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if(m_isActive)
		{
			Update();
			Render();
		}
		else
		{
			WaitMessage();
		}
	}

}
void CDirector::Update()
{
	m_pTimeManager->update(); 
	m_pSceneManager->update();
	m_pInputManager->update();
}
void CDirector::Render()
{
	DrawMgr->drawBegin();
	m_pSceneManager->p_Scene->render();
	DrawMgr->drawEnd();
}
void CDirector::Release()
{
	m_pSceneManager->p_Scene->release();
	delete m_pDrawManager;
	delete m_pSceneManager;
	delete m_pInputManager;
	delete m_pDataManager;
	delete m_pSoundManager;
	delete m_pTimeManager;
	delete m_pTextureManager;
}



CDirector * CDirector::getInstance()
{
	static CDirector * instance;

	if(instance == 0)
	{
		instance = new CDirector();
	}

	return instance;
}


