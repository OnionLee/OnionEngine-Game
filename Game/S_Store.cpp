#include "StdAfx.h"
#include "S_Store.h"
#include "Director.h"


S_Store::S_Store(void)
{
	m_nNowMoney = 0;
	m_nShowMoney = 0;
	m_nSelect = 0;
}


S_Store::~S_Store(void)
{
}

bool S_Store::init()
{
	m_nNowMoney = m_nShowMoney = DataMgr->m_nScore;
	//m_nNowMoney = m_nShowMoney = 10000;
	DataMgr->m_nHp = 120;

	auto spr = CSprite::create("Resource/Store/StoreBack.png");
	addChild(spr);

	for(int i =0; i<3; i++)
	{
		m_pButtons[i] = BuyButton::create();
		m_pButtons[i]->setPos(ccp(345 + (i*270),525));

		m_pButtons[i]->m_pSButton->m_isRender = false;
		m_pButtons[i]->m_pXButton->m_isRender = false;

		addChild(m_pButtons[i]);
	}

	m_pConstLable = CLable::create("신명조");
	m_pConstLable->setText("");
	m_pConstLable->setPos(ccp(310,160));
	m_pConstLable->setSiz(ccp(2,2));
	addChild(m_pConstLable);

	m_pButtons[0]->m_nCost = 3000;
	m_pButtons[1]->m_nCost = 999999;
	m_pButtons[2]->m_nCost = 700;
	return true;
}
void S_Store::update()
{
	CScene::update();



	char buf[64];
	sprintf_s(buf, "%d Point", m_nShowMoney);
	m_pConstLable->setText(buf);

	if(m_nShowMoney > m_nNowMoney)
	{
		m_nShowMoney-=100;
	}

	if(InputMgr->GetKey(Key_Left) == Key_Down)
	{
		if(m_nSelect>0)
		{
			m_nSelect--;
		}

	}
	else if(InputMgr->GetKey(Ket_Right) == Key_Down)
	{
		if(m_nSelect<2)
		{
			m_nSelect++;
		}
	}

	static int i = 0;
	i+= 16;
	if(i>1000)
	if(InputMgr->GetKey(Key_Shot) == Key_Down)
	{
		if(m_nNowMoney - m_pButtons[m_nSelect]->m_nCost >= 0 )
		{
			m_nNowMoney -= m_pButtons[m_nSelect]->m_nCost;
		}

		switch(m_nSelect)
		{
		case 0:
			DataMgr->m_WeaponIndex = Weapon_Double;
			m_pButtons[m_nSelect]->m_nCost = 999999;
			m_pButtons[m_nSelect+1]->m_nCost = 6000;
			break;
		case 1:
			DataMgr->m_WeaponIndex = Weapon_Tripel;
			m_pButtons[m_nSelect]->m_nCost = 999999;
			break;
		case 2:
			DataMgr->m_nGrenade++;
			if(m_nNowMoney<300)
			m_pButtons[m_nSelect]->m_nCost = 999999;
			break;
		}
	}

	for(int i = 0; i<3; i++)
	{
		if(i == m_nSelect)
		{
			m_pButtons[i]->m_pSButton->m_isRender = true;
		}
		else
		{
			m_pButtons[i]->m_pSButton->m_isRender = false;
		}

		if(m_pButtons[i]->m_nCost > m_nNowMoney)
		{
			m_pButtons[i]->m_pConstLable->setText("구매불가");
			m_pButtons[i]->m_pConstLable->setAcp(ccp(0.5,0.5));
			m_pButtons[i]->m_pXButton->m_isRender = true;
		}
		else
		{
			char buf[64];
			sprintf_s(buf, "%d Point", m_pButtons[i]->m_nCost);
			m_pButtons[i]->m_pConstLable->setText(buf);
			m_pButtons[i]->m_pConstLable->setAcp(ccp(0.5,0.5));
			m_pButtons[i]->m_pXButton->m_isRender = false;
		}

	}

	if(InputMgr->GetKey(Key_Jump) == Key_Down)
	{
		SceneMgr->NowSceneChange(S_Stage2);
	}



}
