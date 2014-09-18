#pragma once
#include "DrawManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "TextureManager.h"

class CDirector
{
public:
	CDirector(void);
	~CDirector(void);

	CDrawManager * m_pDrawManager;
	CSceneManager * m_pSceneManager;
	CInputManager * m_pInputManager;
	CDataManager * m_pDataManager;
	CSoundManager * m_pSoundManager;
	CTimeManager * m_pTimeManager;
	CTextureManager * m_pTextureManager;

	CDrawManager * getDrawManager(){return m_pDrawManager;}
	CSceneManager * getSceneManager(){return m_pSceneManager;}
	CInputManager * getInputManager(){return m_pInputManager;}
	CDataManager * getDataManager(){return m_pDataManager;}
	CSoundManager * getSoundManager(){return m_pSoundManager;}
	CTimeManager * getTimeManager(){return m_pTimeManager;}
	CTextureManager * getTextureManager(){return m_pTextureManager;}
	void Init();
	void Loop();
	void Update();
	void Render();
	void Release();

	bool m_isActive;

	static CDirector * getInstance();
};

#define CDIRECTOR CDirector::getInstance()
#define DrawMgr CDirector::getInstance()->getDrawManager()
#define SceneMgr CDirector::getInstance()->getSceneManager()
#define InputMgr CDirector::getInstance()->getInputManager()
#define DataMgr CDirector::getInstance()->getDataManager()
#define SoundMgr CDirector::getInstance()->getSoundManager()
#define TimeMgr CDirector::getInstance()->getTimeManager()
#define TexMgr CDirector::getInstance()->getTextureManager()