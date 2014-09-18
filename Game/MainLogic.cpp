#include "StdAfx.h"
#include "MainLogic.h"
#include "Director.h"


MainLogic::MainLogic(void)
{
	for(int i = 0; i<5; i++)
		m_pFlag[i] = false;

	m_NowFlag = 0;
	//보스가 없는 상태
	m_pBoss = 0;

}


MainLogic::~MainLogic(void)
{
}

bool MainLogic::init()
{
	if(!CLayer::init())
		return false;

	m_pBackground1 = CSprite::create("Resource/Stage/background_1.png");
	addChild(m_pBackground1,5);

	auto m_pBackground3 = CSprite::create("Resource/Stage/background_1.png");
	m_pBackground3->setPos(ccp(5000,0));
	addChild(m_pBackground3,5);

	m_pBackground2 = CSprite::create("Resource/Stage/background_2.png");
	m_pBackground2->setPos(ccp(5000,0));
	addChild(m_pBackground2,5);


	//제일앞에 있어야 하는 포그라운드
	m_pForeground = CSprite::create("Resource/Stage/foreground.png");
	m_pForeground->setPos(ccp(4800,0));
	addChild(m_pForeground,-5);


		//렉걸려서 미리 로드함
	TexMgr->LoadTexture("Resource/Bullet/bang_0.png");
	TexMgr->LoadTexture("Resource/Bullet/bang_1.png");
	TexMgr->LoadTexture("Resource/Bullet/bang_2.png");
	TexMgr->LoadTexture("Resource/Bullet/bang_3.png");


	return true;
}

void MainLogic::update()
{

	if(DataMgr->m_isActive)
	{
	CLayer::update();

	charUpdate();

	bulletUpdate();

	itemUpdate();

	boxUpdate();

	//플래그 업데이트
	FlagOn();

	if(m_pPlayer->getPos().x > 600)
		setPos(ccp(-m_pPlayer->getPos().x + 600, getPos().y));
	DataMgr->stageUpdate();
	}
}

void MainLogic::MakeBullet(CBaseChar * p_target)
{
	CBullet * temp = NULL;
	D3DXVECTOR2 t;
	bool playerBullet = false;
	if(p_target->m_eCharIndex == Index_Player)
	{
		playerBullet = true;
	}
	else
	{
		playerBullet = false;
	}


	switch(p_target->m_eNowWeapon)
	{
	case Weapon_Nomal:
		temp = new CBullet();
		temp->init(Index_Nomal);
		t = p_target->getPos();
		t.x += p_target->m_pArm->getPos().x * p_target->m_Siz.x;
		t.y += p_target->m_pArm->getPos().y;
		temp->shotbullet(t,p_target->m_vWeaponVector,playerBullet);
		m_vBullets.push_back(temp);
		addChild(temp);
		p_target->m_isFire = false;
		break;
	case Weapon_Double:
		for(int i =0; i<2; i++)
		{
			temp = new CBullet();
			temp->init(Index_Double);
			t = p_target->getPos();
			t.x += p_target->m_pArm->getPos().x* p_target->m_Siz.x;
			t.y += p_target->m_pArm->getPos().y;
			t.y +=  (20 * i) - 10;
			temp->shotbullet(t,p_target->m_vWeaponVector,playerBullet);
			m_vBullets.push_back(temp);
			addChild(temp);
		}
		p_target->m_isFire = false;
		break;
	case Weapon_Tripel:
		for(int i =0; i<3; i++)
		{
			temp = new CBullet();
			temp->init(Index_Double);
			t = p_target->getPos();
			t.x += p_target->m_pArm->getPos().x* p_target->m_Siz.x;
			t.y += p_target->m_pArm->getPos().y;
			t.y +=  (20 * i) - 20;
			temp->shotbullet(t,p_target->m_vWeaponVector,playerBullet);
			m_vBullets.push_back(temp);
			addChild(temp);
		}
		p_target->m_isFire = false;
		break;
	case Weapon_Multiple:
		temp = new CBullet();
		temp->init(Index_Multiple);
		t = p_target->getPos();
		t.x += p_target->m_pArm->getPos().x* p_target->m_Siz.x;
		t.y += p_target->m_pArm->getPos().y;
		temp->shotbullet(t,p_target->m_vWeaponVector,playerBullet);
		m_vBullets.push_back(temp);
		addChild(temp);
		break;
	case Weapon_BigMulti:
		temp = new CBullet();
		temp->init(Index_BigMulti);
		t = p_target->getPos();
		t.x += p_target->m_pArm->getPos().x* p_target->m_Siz.x;
		t.y += p_target->m_pArm->getPos().y;
		temp->shotbullet(t,p_target->m_vWeaponVector,playerBullet);
		m_vBullets.push_back(temp);
		addChild(temp);
		break;


	}
}

void MainLogic::MakeGrenade()
{
	auto temp = new CGrenade();
	temp->init(Index_Grenade);
	temp->shotbullet(m_pPlayer->getPos(),m_pPlayer->m_vWeaponVector,true);
	m_vBullets.push_back(temp);
	addChild(temp);
	m_pPlayer->isGrenade = false;
}


void MainLogic::charUpdate()
{
	


	auto itr = m_vChars.begin();
	FOREACH(m_vChars,itr)
	{
		if((*itr)->m_isFire)
		{
			MakeBullet((*itr));
		}

		if((*itr)->m_eState == StateB_Null)
		{
			if((*itr)->m_eCharIndex == Index_Player)
			{

			}
			else
			{
				auto t = *itr;
				m_vChars.erase(itr);
				removeChild(t);
				break;
			}
		}
	}

	if(m_pPlayer->isGrenade)
	{
		MakeGrenade();
	}

	if(m_pPlayer->m_nHp <= 0)
	{
		DataMgr->m_isActive = false;
		MakeItem(ItemIndex::ItemBomb,m_pPlayer->getPos().x);
	}
}

void MainLogic::bulletUpdate()
{
	auto itr1 = m_vBullets.begin();
	FOREACH(m_vBullets,itr1)
	{

		if((*itr1)->m_eState == StateB_Crash)
		{
			if((*itr1)->m_eIndex == Index_Grenade)
			{
				auto itr3 = m_vChars.begin();
				FOREACH(m_vChars,itr3)
				{
					if((*itr3)->m_eCharIndex != Index_Player)
						if((*itr1)->CircleByCircle(*itr3,90000))
						{
							(*itr3)->Attacked((*itr1)->m_nPower);
						}
				}
				(*itr1)->m_eState = StateB_Die;
			}
		}

		auto itr2 = m_vChars.begin();
		FOREACH(m_vChars,itr2)
		{
			if((*itr1)->m_eState == StateB_Life && (*itr2)->m_eState != State_Die && (*itr2)->m_eState != State_Null)
			{
				if((*itr1)->RectByRect(*itr2))
				{
					if((*itr1)->m_isPlayerBullet&&(*itr2)->m_eCharIndex != Index_Player)
					{
						if((*itr1)->m_eState == StateB_Life)
							(*itr1)->m_eState = StateB_Crash;
						(*itr2)->Attacked((*itr1)->m_nPower);
					}
					else if(!(*itr1)->m_isPlayerBullet&&(*itr2)->m_eCharIndex == Index_Player)
					{
						if((*itr1)->m_eState == StateB_Life)
							(*itr1)->m_eState = StateB_Crash;
						(*itr2)->Attacked((*itr1)->m_nPower);
						m_pPlayer->setWeapon(m_pPlayer->m_eNomallWeaponState);
					}
				}
			}
		}

		if((*itr1)->m_eState == StateB_Null)
		{
			auto t = *itr1;
			m_vBullets.erase(itr1);
			removeChild(t);
			break;
		}
	}
}

void MainLogic::boxUpdate()
{
	auto itr1 = m_vBoxs.begin();
	FOREACH(m_vBoxs,itr1)
	{
		auto itr2 = m_vBullets.begin();
		FOREACH(m_vBullets,itr2)
		{
			if((*itr2)->m_eState == StateB_Life)
			{
				if((*itr1)->RectByRect(*itr2))
				{
					(*itr1)->Attacked((*itr2)->m_nPower);
					(*itr2)->m_eState = StateB_Die;
				}
			}

		}

		auto itr3 = m_vChars.begin();
		FOREACH(m_vChars,itr3)
		{
			if((*itr1)->RectByRect(*itr3))
			{
				if((*itr3)->m_eCharIndex == Index_Player)
				{
					if(m_pPlayer->m_eCollider == Coll_Air)
					{
						boxUpper((*itr1));
					}
					else
					{
						boxCrash((*itr3),(*itr1));
					}
				}
				else
				{
					boxCrash((*itr3),(*itr1));
				}
			}
			else
			{
				if((*itr3)->m_eCharIndex == Index_Player)
				{
					if((*itr1)->m_isOnBox)
					{
						(*itr1)->m_isOnBox = false;
						m_pPlayer->m_eCollider = Coll_Air;
					}
				}
			}

		}

		if((*itr1)->m_isOnBox)
		{
			m_pPlayer->m_eCollider = Coll_Box;
		}

		if((*itr1)->m_eState == BoxNull)
		{
			removeChild(*itr1);
			m_vBoxs.erase(itr1);
			break;
		}

	}
}

void MainLogic::boxUpper(CBox * box)
{
	if(m_pPlayer->m_vMoveVector.y > 0)
	{
		box->m_isOnBox = true;
	}
}

void MainLogic::boxCrash(CBaseChar * Charic , CBox * box)
{
	//상자의 오른쪽 
	if(box->getPos().x <  Charic->getPos().x)
	{
		Charic->setPos(ccp(box->getPos().x + (box->getRect().right * 0.7), Charic->getPos().y));
	}
	//상자의 왼쪽
	else
	{
		Charic->setPos(ccp(box->getPos().x - (box->getRect().right * 0.7)
			, Charic->getPos().y));
	}

}

void MainLogic::itemUpdate()
{
	auto itr1 = m_vItems.begin();
	FOREACH(m_vItems,itr1)
	{
		if((*itr1)->CircleByCircle(m_pPlayer,10000))
		{
			switch((*itr1)->m_eIndex)
			{
			case ItemGrenade:
				m_pPlayer->m_nGrenade += 10;
				break;
			case ItemMultiple:
				m_pPlayer->setWeapon(Weapon_Multiple);
				break;
			case ItemBigMulti:
				m_pPlayer->setWeapon(Weapon_BigMulti);
				break;
			case ItemBomb:
				for(int i =0; i<10; i++)
				{
					auto temp = new CGrenade();
					temp->init(Index_Grenade);
					temp->shotbullet(ccp(m_pPlayer->getPos().x + (i * 100) - 1300,0),ccp(1,0),true);
					temp->setTex(TexMgr->LoadTexture("Resource/Bullet/bomb.png"));
					m_vBullets.push_back(temp);
					addChild(temp);
				}
				break;
			case ItemSuper:
				m_pPlayer->isSuper = true;
				break;
			case ItemLife:
				m_pPlayer->m_nHp += 20;
				break;
			}
			auto t = *itr1;
			m_vItems.erase(itr1);
			removeChild(t);
			break;
		}
	}

}

void MainLogic::FlagOn()
{
	if(m_pFlag[m_NowFlag])
	{
		m_pFlag[m_NowFlag] = false;
		switch(m_NowFlag)
		{
		case 0:
			Flag1();
			m_NowFlag++;
			break;
		case 1:
			Flag2();
			m_NowFlag++;
			break;
		case 2:
			Flag3();
			m_NowFlag++;
			break;
		case 3:
			Flag4();
			m_NowFlag++;
			break;
		case 4:
			Flag5();
			m_NowFlag++;
			break;
		}

	}
}

void MainLogic::MakeEnemy(CharIndex index , int x)
{
	auto t = CEnemy::create(index);
	t->setPos(ccp(x,300));
	m_vChars.push_back(t);
	addChild(t,-10);
}
void MainLogic::MakeBox(BoxIndex index , int x)
{

	if(index == Box_Trap)
	{
		auto * t = new CTrap();
		t->init();
		t->setPos(ccp(x,TRRAPGROUND));
		m_vBoxs.push_back(t);
		addChild(t,-10);
	}
	else
	{
		auto * t = new CConBox();
		t->init();
		t->setPos(ccp(x,TRRAPGROUND));
		m_vBoxs.push_back(t);
		addChild(t,-10);
	}
}
void MainLogic::MakeItem(ItemIndex index , int x)
{
	auto t = CItemBox::create(index);
	t->setPos(ccp(x,ITEMGROUND));
	m_vItems.push_back(t);
	addChild(t,-10);
}

void MainLogic::release()
{
	//auto itr = m_vChars.begin();
	//FOREACH(m_vChars,itr)
	//{
	//	removeChild(*itr);
	//}
	//m_vChars.clear();

	//m_vBullets.clear();
	//m_vItems.clear();
	//m_vBoxs.clear();
	//CLayer::release();
}