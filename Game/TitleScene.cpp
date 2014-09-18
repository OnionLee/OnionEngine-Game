#include "StdAfx.h"
#include "TitleScene.h"
#include "Director.h"



CTitleScene::CTitleScene(void)
{
}


CTitleScene::~CTitleScene(void)
{
}


bool CTitleScene::init()
{
	m_nSelcnum = 0;
	m_nSceneCount = 0;

	m_pBackGround = CSprite::create("Resource/Title/back.png");
	addChild(m_pBackGround);

	m_pPangPare = CSprite::create("Resource/Title/pang.png");
	m_pPangPare->setAcp(ccp(0.5,0.5));
	m_pPangPare->setPos(ccp(1280/2,1024));
	addChild(m_pPangPare);

	m_pForeGround = CSprite::create("Resource/Title/fore.png");
	addChild(m_pForeGround);

	for(int i =0; i<5; i++)
	{
		char path[64];
		sprintf_s(path, "Resource/Title/button_%d.png", i);
		m_pButtons[i] = CSprite::create(path);
		m_pButtons[i]->setAcp(ccp(0.5,0.5));
		m_pButtons[i]->setPos(ccp(930,300 + (i*120)));
		addChild(m_pButtons[i]);
	}
	
	return true;
}
void CTitleScene::update()
{
	CScene::update();

	menuUpdate();
	buttonUpdate();
	pangUpdate();
}

void CTitleScene::menuUpdate()
{
	if(InputMgr->GetKey(Key_Up) == KeyState::sKey_Down)
	{
		if(m_nSelcnum>0)
		{
			m_nSceneCount = 0;
			m_nSelcnum--;
		}
	}
	else if(InputMgr->GetKey(Key_Down) == KeyState::sKey_Down)
	{
		if(m_nSelcnum<4)
		{
			m_nSceneCount = 0;
			m_nSelcnum++;
		}
	}
	else if(InputMgr->GetKey(Key_Shot) == KeyState::sKey_Down)
	{
		printf("%d Select!!!",m_nSelcnum);
		switch(m_nSelcnum)
		{
		case 0:
			SceneMgr->NowSceneChange(S_Stage1);
			break;
		case 1:
			SceneMgr->NowSceneChange(S_HowToPlay);
			break;
		case 2:
			SceneMgr->NowSceneChange(S_Rank);
			break;
		case 3:
			SceneMgr->NowSceneChange(S_Make);
			break;
		case 4:
			exit(0);
			break;
		}
	}


	for(int i = 0; i<5; i++)
	{
		if(i == m_nSelcnum)
		{
			buttonUpdate();
		}
		else
		{
			m_pButtons[i]->setSiz(ccp(1,1));
		}
	}
}
void CTitleScene::buttonUpdate()
{
	m_nSceneCount+=TimeMgr->m_nDetaTime;

	if(m_nSceneCount<400)
	{
		m_pButtons[m_nSelcnum]->setSiz(ccp(m_pButtons[m_nSelcnum]->getSiz().x + 0.01f,
											m_pButtons[m_nSelcnum]->getSiz().y + 0.01f));
	}
	else if(m_nSceneCount<800)
	{
		if(m_pButtons[m_nSelcnum]->getSiz().x > 1)
		m_pButtons[m_nSelcnum]->setSiz(ccp(m_pButtons[m_nSelcnum]->getSiz().x - 0.01f,
											m_pButtons[m_nSelcnum]->getSiz().y - 0.01f));
	}
	else
	{
		m_nSceneCount = 0;
	}
	
}
void CTitleScene::pangUpdate()
{
	m_pPangPare->setRot(m_pPangPare->getRot() + 0.02f);
}