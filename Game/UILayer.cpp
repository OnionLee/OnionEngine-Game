#include "StdAfx.h"
#include "UILayer.h"
#include "Director.h"


UILayer::UILayer(void)
{
}


UILayer::~UILayer(void)
{
}

bool UILayer::init()
{
	if(!CLayer::init())
		return false;

	m_pPanal = CSprite::create("Resource/UI/UI_Panel.png");
	m_pPanal->setPos(ccp(0,0));
	addChild(m_pPanal);

	m_pNameLabel = CLable::create("신명조");
	m_pNameLabel->setAcp(ccp(0,0));
	m_pNameLabel->setPos(ccp(250,40));
	m_pNameLabel->setCor(ccc4(255,255,255,255));
	m_pNameLabel->setSiz(ccp(0.5,0.5));
	addChild(m_pNameLabel);
		
	m_pHpLable = CLable::create("신명조");
	m_pHpLable->setAcp(ccp(1,0));
	m_pHpLable->setPos(ccp(320,82));
	m_pHpLable->setCor(ccc4(255,255,255,255));
	m_pHpLable->setSiz(ccp(0.5,0.5));
	addChild(m_pHpLable);

	m_pGrenadeLabel = CLable::create("신명조");
	m_pGrenadeLabel->setAcp(ccp(1,0));
	m_pGrenadeLabel->setPos(ccp(320,127));
	m_pGrenadeLabel->setCor(ccc4(255,255,255,255));
	m_pGrenadeLabel->setSiz(ccp(0.5,0.5));
	addChild(m_pGrenadeLabel);

	m_pScoreLabel = CLable::create("신명조");
	m_pScoreLabel->setAcp(ccp(0,0.5));
	m_pScoreLabel->setPos(ccp(600,200));
	m_pScoreLabel->setCor(ccc4(255,255,255,255));
	m_pScoreLabel->setSiz(ccp(0.5,0.5));
	addChild(m_pScoreLabel);

	m_pDie= CSprite::create("Resource/Stage/DiePanal.png");
	addChild(m_pDie);
	m_pDie->m_isRender = false;

	m_pRestartLable = CLable::create("신명조");
	m_pRestartLable->setText("10");
	m_pRestartLable->setSiz(ccp(2,2));
	m_pRestartLable->setAcp(ccp(0.5,0.5));
	m_pRestartLable->setPos(ccp(1280/2,1024/2));
	m_pRestartLable->m_isRender = false;
	addChild(m_pRestartLable);

	m_nRestratCount = 10;
	m_nTickCount = 0;


	return true;
}
void UILayer::update()
{
	CLayer::update();

	char buf[128];
	m_pNameLabel->setText(DataMgr->m_sName.c_str());

	sprintf_s(buf,"%d",DataMgr->m_nHp);
	m_pHpLable->setText(buf);

	sprintf_s(buf, "%d", DataMgr->m_nGrenade);
	m_pGrenadeLabel->setText(buf);

	sprintf_s(buf, "%d", DataMgr->m_nScore);
	m_pScoreLabel->setText(buf);

	m_pGrenadeLabel->setAcp(ccp(1,0));
	m_pHpLable->setAcp(ccp(1,0));

	if(!DataMgr->m_isActive)
		reStartUpdate();
}

void UILayer::reStartUpdate()
{
	m_nTickCount += 16;
	m_pRestartLable->m_isRender = true;
	char buf[4];
	sprintf_s(buf, "%d", m_nRestratCount);
	m_pRestartLable->setText(buf);

	m_pDie->m_isRender = true;

	if(m_nTickCount> 1000)
	{
		if(m_nRestratCount<0)
		{
			SceneMgr->NowSceneChange(S_Rank);
		}

		m_nRestratCount--;
		m_nTickCount = 0;
	}

	if(InputMgr->GetKey(Key_Shot) == sKey_Down)
	{
		DataMgr->m_pPlayer->m_nHp = 100;
		DataMgr->m_pPlayer->m_eState = State_Idel;
		m_pRestartLable->m_isRender = false;
		m_pDie->m_isRender = false;
		DataMgr->m_isActive = true;
	}
	else if(InputMgr->GetKey(Key_Jump) == sKey_Down)
	{
		SceneMgr->NowSceneChange(S_Rank);
	}
}