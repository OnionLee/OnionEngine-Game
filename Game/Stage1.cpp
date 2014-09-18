#include "StdAfx.h"
#include "Stage1.h"
#include "Director.h"
#include "ItemBox.h"

Stage1::Stage1(void)
{

}


Stage1::~Stage1(void)
{
}

bool Stage1::init()
{
	if(!MainLogic::init())
		return false;

	DataMgr->statgeReset();

	m_pPlayer = CPlayer::create();
	m_vChars.push_back(m_pPlayer);
	addChild(m_pPlayer,1);

	DataMgr->setPlayer(m_pPlayer);

	return true;
}
void Stage1::update()
{
	MainLogic::update();

	if(m_pBoss!=0)
	if(m_pBoss->m_nHp <= 0)
	{
		SceneMgr->NowSceneChange(S_Store);
	}


	if(m_pPlayer->getPos().x < 1500)
	{
		m_pFlag[0] = true;
	}
	else if(m_pPlayer->getPos().x < 3000)
	{
		m_pFlag[1] = true;
	}
	else if(m_pPlayer->getPos().x < 4500)
	{
		m_pFlag[2] = true;
	}
	else if(m_pPlayer->getPos().x < 6000)
	{
		m_pFlag[3] = true;
	}
	else if(m_pPlayer->getPos().x < 7500)
	{
		m_pFlag[4] = true;
	}
}

void Stage1::Flag1()
{
	for(int i = 0; i<10; i++)
	{
		MakeEnemy(Index_Enemy1,150*i);
		
	}
	MakeItem(ItemIndex::ItemGrenade,1000);
	MakeItem(ItemIndex::ItemBomb,1500);

	for(int i = 0; i<3; i++)
	{
		MakeBox(BoxIndex::Box_ConBox, i * 2300);
	}
}
void Stage1::Flag2()
{
	for(int i = 0; i<5; i++)
	{
		MakeEnemy(Index_Enemy1,1500 + 150*i);
		MakeEnemy(Index_Enemy2,2250 + 150*i);
		MakeItem(ItemIndex::ItemMultiple,1000 * i);
	}
	MakeItem(ItemIndex::ItemGrenade,2000);
}
void Stage1::Flag3()
{
	for(int i = 0; i<10; i++)
	{
		MakeEnemy(Index_Enemy2,3000 + 150*i);
	}
	MakeItem(ItemIndex::ItemSuper,3000);
	MakeItem(ItemIndex::ItemBomb,3500);
}
void Stage1::Flag4()
{
	for(int i = 0; i<20; i++)
	{
		MakeEnemy(Index_Enemy2,4500 + 75*i);
	}
	MakeItem(ItemIndex::ItemLife,4000);
}
void Stage1::Flag5()
{
	for(int i = 0; i<5; i++)
	{
		MakeEnemy(Index_Enemy1,6000 + 150*i);
		MakeEnemy(Index_Enemy2,6750 + 150*i);
	}

	MakeItem(ItemIndex::ItemBomb,5000);

	m_pBoss = CEnemy::create(Index_Boss1);
	m_pBoss->setPos(ccp(7000,0));
	addChild(m_pBoss);
	m_vChars.push_back(m_pBoss);

}