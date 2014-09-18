#include "StdAfx.h"
#include "OpeningScene.h"
#include "Director.h"

OpeningScene::OpeningScene(void)
{
	m_isOp1 = false;
	m_isOp2 = false;
	m_isOp3 = false;
}


OpeningScene::~OpeningScene(void)
{
}

bool OpeningScene::init()
{
	if(!CScene::init())
		return false;

	m_isOp1 = true;

	auto a = CSprite::create("Resource/Opening/Back.png");
	addChild(a,4);

	m_pOp1 = CSprite::create("Resource/Opening/OP_1.png");
	m_pOp1->setPos(ccp(-1280,0));
	addChild(m_pOp1,3);

	m_pOp2 = CSprite::create("Resource/Opening/OP_2.png");
	m_pOp2->setPos(ccp(1280,0));
	addChild(m_pOp2,2);

	m_pOp3 = CSprite::create("Resource/Opening/OP_3.png");
	m_pOp3->setPos(ccp(0,2048));
	addChild(m_pOp3,1);

	m_isOp1 = true;

	SoundMgr->PlayerSound("Resource/Sound/bgm1.mp3",true,1);

	return true;
}

void OpeningScene::update()
{
	if(m_isOp1)
	{
		m_pOp1->setPos(ccp(m_pOp1->getPos().x + 10,0));
		if(m_pOp1->getPos().x > 0)
		{
			m_pOp1->setPos(ccp(0,0));
			m_isOp2 = true;
			m_isOp1 = false;
		}
	}
	else if(m_isOp2)
	{
		m_pOp2->setPos(ccp(m_pOp2->getPos().x - 10,0));
		if(m_pOp2->getPos().x < 0)
		{
			m_pOp2->setPos(ccp(0,0));
			m_isOp3 = true;
			m_isOp2 = false;
		}
	}
	else if(m_isOp3)
	{
		m_pOp3->setPos(ccp(0,m_pOp3->getPos().y - 10));
		if(m_pOp3->getPos().y < 0)
		{
			m_pOp3->setPos(ccp(0,0));
			m_isOp3 = false;
		}
	}
	else
	{
		if(InputMgr->GetKey(Key_Shot) == sKey_Down)
		{
			SceneMgr->NowSceneChange(S_Title);
		}
	}
}