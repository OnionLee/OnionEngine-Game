#pragma once
#include "Layer.h"
#include "Player.h"
#include "Bullet.h"
#include "BaseChar.h"
#include "Enemy.h"
#include "Grenade.h"
#include "ItemBox.h"
#include "ConBox.h"
#include "Trap.h"
#include "Box.h"

#define TRRAPGROUND 800
#define ITEMGROUND 800

class MainLogic : public CLayer
{
public:
	virtual bool init();
	virtual void update();
	virtual void release();

	CPlayer * m_pPlayer;
	CEnemy * m_pBoss;
	CSprite * m_pBackground1;
	CSprite * m_pBackground2;
	CSprite * m_pForeground;

	std::vector<CBaseChar*> m_vChars;
	std::vector<CBullet *> m_vBullets;
	std::vector<CItemBox *> m_vItems;
	std::vector<CBox *> m_vBoxs;

	void MakeBullet(CBaseChar * p_target);
	void MakeGrenade();

	void charUpdate();
	void bulletUpdate();
	void boxUpdate();
	void itemUpdate();

	void boxCrash(CBaseChar * Charic , CBox * box);
	void boxUpper(CBox * box);

	void MakeEnemy(CharIndex index , int x);
	void MakeBox(BoxIndex index , int x);
	void MakeItem(ItemIndex index , int x);

	//새로운 몬스터
	bool m_pFlag[5];
	int m_NowFlag;
	void FlagOn();
	virtual void Flag1(){}
	virtual void Flag2(){}
	virtual void Flag3(){}
	virtual void Flag4(){}
	virtual void Flag5(){}


	MainLogic(void);
	~MainLogic(void);
};

