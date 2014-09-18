#include "StdAfx.h"
#include "Trap.h"


CTrap::CTrap(void)
{
	m_nAttackTime = 0;
	m_isAttacking = false; 
}


CTrap::~CTrap(void)
{
}

bool CTrap::init()
{
	CBox::init();
	CSprite::init("Resource/Box/box_0.png");
	m_pDieAni = new CAnimation();
	m_pDieAni->init(100,false);
	m_pDieAni->addFrame("Resource/Box/box_0.png");
	m_pDieAni->addFrame("Resource/Box/box_1.png");
	m_pDieAni->addFrame("Resource/Box/box_2.png");
	m_pDieAni->addFrame("Resource/Box/box_3.png");

	m_index = Box_Trap;

	m_nHp = 50;

	setAcp(ccp(0.5,0.5));
	setBoundBox();

	return true;
}
void CTrap::update()
{
	CBox::update();

	Attacking();

}

void CTrap::Attacking()
{
	if(m_isAttacking)
	{
		m_nAttackTime+=16;
		this->setCor(ccc4(255,255,0,0));
		if(m_nAttackTime>200)
		{
			this->setCor(ccc4(255,255,255,255));
			m_nAttackTime = 0;
			m_isAttacking = false;
		}
	}
}

CTrap * CTrap::craete()
{
	auto t = new CTrap();
	t->init();
	
	return t;
}

void CTrap::Attacked(int Power)
{
	m_nHp -= Power;
	if(m_nHp <= 0)
	{
		m_eState = BoxDie;
	}
}