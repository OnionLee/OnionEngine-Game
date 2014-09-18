#include "StdAfx.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "OpeningScene.h"
#include "GameScene.h"
#include "S_Ending.h"
#include "S_Maker.h"
#include "S_Store.h"
#include "S_Rank.h"
#include "S_HowToPlay.h"

CSceneManager::CSceneManager(void)
{
	p_Scene = NULL;
	m_isNextScene = false;
}


CSceneManager::~CSceneManager(void)
{
}

void CSceneManager::init()
{
	SceneChange(S_Opening);
}

//신전환 다음업데이트에 실행되도록 설정
//m_isNextScene < - 이변수르 이영
void CSceneManager::SceneChange(SceneIndex index)
{
		if(p_Scene != NULL)
		{
			p_Scene->release();
			delete p_Scene;
			p_Scene = NULL;
		}
		switch(index)
		{
		case S_Title:
			setScene(CTitleScene::create());
			break;
		case S_Opening:
			setScene(OpeningScene::create());
			break;
		case S_Stage1:
			setScene(GameScene::createStage1());
			break;
		case S_HowToPlay:
			setScene(S_HowToPlay::create());
			break;
		case S_Store:
			setScene(S_Store::create());
			break;
		case S_Stage2:
			setScene(GameScene::createStage2());
			break;
		case S_Ending:
			setScene(S_Ending::create());
			break;
		case S_Rank:
			setScene(S_Rank::create());
			break;
		case S_Make:
			setScene(S_Maker::create());
			break;
		}
}

void CSceneManager::update()
{
	if(m_isNextScene)
	{
		SceneChange(m_eNextScene);
		m_isNextScene = false;
	}

	p_Scene->update();
}

void CSceneManager::NowSceneChange(SceneIndex index)
{
	m_isNextScene = true;
	m_eNextScene = index;
	
}