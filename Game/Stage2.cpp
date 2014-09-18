#include "StdAfx.h"
#include "Stage2.h"
#include "Director.h"


Stage2::Stage2(void)
{
}


Stage2::~Stage2(void)
{
}

bool Stage2::init()
{
	if(!MainLogic::init())
		return false;

	m_pPlayer = CPlayer::create();
	m_pPlayer->setPos(ccp(7550,0));
	m_vChars.push_back(m_pPlayer);
	addChild(m_pPlayer,1);

	CLable * lable = CLable::create("신명조");
	lable->setText("스테이지 2 레이어");
	lable->setPos(ccp(0,100));
	addChild(lable);

	DataMgr->setPlayer(m_pPlayer);

	m_pPlayer->m_eNowWeapon = m_pPlayer->m_eNomallWeaponState;

	return true;
}
void Stage2::update()
{
	MainLogic::update();

	if(m_pBoss!=0)
	if(m_pBoss->m_nHp <= 0)
	{
		SceneMgr->NowSceneChange(S_Rank);
	}


	if(m_pPlayer->getPos().x > 7500)
	{
		m_pFlag[0] = true;
	}
	else if(m_pPlayer->getPos().x > 6000)
	{
		m_pFlag[1] = true;
	}
	else if(m_pPlayer->getPos().x > 4500)
	{
		m_pFlag[2] = true;
	}
	else if(m_pPlayer->getPos().x > 3000)
	{
		m_pFlag[3] = true;
	}
	else if(m_pPlayer->getPos().x > 1500)
	{
		m_pFlag[4] = true;
	}
}

void Stage2::Flag1()
{
	for(int i = 0; i<10; i++)
	{
		MakeEnemy(Index_Enemy1, 5000 + 150*i);

	}
	MakeItem(ItemIndex::ItemGrenade,6000);
	MakeItem(ItemIndex::ItemBomb,6500);
	
	for(int i = 0; i<3; i++)
	{
		MakeBox(BoxIndex::Box_ConBox, i * 2300);
	}

}
void Stage2::Flag2()
{
	for(int i = 0; i<5; i++)
	{
		MakeEnemy(Index_Enemy1,4000 + 150*i);
		MakeEnemy(Index_Enemy2,4250 + 150*i);
		MakeItem(ItemIndex::ItemMultiple,4000 + 1000 * i);
	}
	MakeItem(ItemIndex::ItemGrenade,5000);
}
void Stage2::Flag3()
{
	for(int i = 0; i<10; i++)
	{
		MakeEnemy(Index_Enemy2,3000 + 150*i);
	}
	MakeItem(ItemIndex::ItemSuper,3000);
	MakeItem(ItemIndex::ItemBomb,3500);
}
void Stage2::Flag4()
{
	for(int i = 0; i<20; i++)
	{
		MakeEnemy(Index_Enemy2,2000 + 75*i);
	}
	MakeItem(ItemIndex::ItemLife,2000);
}
void Stage2::Flag5()
{
	for(int i = 0; i<5; i++)
	{
		MakeEnemy(Index_Enemy1,0 + 150*i);
		MakeEnemy(Index_Enemy2,0 + 150*i);
	}

	MakeItem(ItemIndex::ItemBomb,0);

	m_pBoss = CEnemy::create(Index_Boss2);
	m_pBoss->setPos(ccp(300,0));
	addChild(m_pBoss);
	m_vChars.push_back(m_pBoss);

}