#include "StdAfx.h"
#include "Enemy.h"
#include "Director.h"


CEnemy::CEnemy(void)
{
	m_naiStateTime = 0;
	m_naiNextTime = 0;
	m_nShotTime = 0;
}


CEnemy::~CEnemy(void)
{

}

bool CEnemy::init(CharIndex index)
{
	if(!CBaseChar::init(index))
		return false;

	stateChange();

	return true;
}

void CEnemy::update()
{
	CBaseChar::update();

	if(m_eState != State_Die && m_eState != State_Null)
	{
		aiUpdate();
	}

}

CEnemy * CEnemy::create(CharIndex index)
{
	CEnemy * temp = new CEnemy();
	if(!temp->init(index))
	{
		delete temp;
		temp = NULL;
		return NULL;
	}

	return temp;
}

void CEnemy::aiUpdate()
{
	lookState();

	m_naiStateTime+= TimeMgr->m_nDetaTime;

	switch(m_eAiState)
	{
	case ai_Idel:
		m_eState = State_Idel;
		break;
	case ai_Walk:
		m_eState = State_Run;
		break;
	case ai_Shot:
		shotState();
		break;
	}

	if(m_naiStateTime>m_naiNextTime)
	{

		m_naiStateTime = 0;
		stateChange();

	}
}

void CEnemy::stateChange()
{
	m_naiNextTime = ((rand()%5)+1) * 400;
	m_eAiState = (aiState)(rand()%3);
}

void CEnemy::shotState()
{
	m_nShotTime+= 16;
	m_isFire = false;

	if(m_eNowWeapon == Weapon_Multiple || m_eNowWeapon == Weapon_BigMulti)
	{
		if(m_nShotTime>100)
		{
			m_isFire = true;
			m_nShotTime = 0;
		}
	}
	else
	{
		if(m_nShotTime>500)
		{
			m_isFire = true;
			m_nShotTime = 0;
		}
	}
}

void CEnemy::lookState()
{
	if(DataMgr->m_pPlayer->getPos().x > getPos().x + 200)
	{
		m_eLook = Look_Right;
	}
	else if(DataMgr->m_pPlayer->getPos().x < getPos().x - 200)
	{
		m_eLook = Look_Left;
	}

	if(DataMgr->m_pPlayer->getPos().y > getPos().y + 10)
	{
		if(m_eLook == Look_Right)
		{
			m_eLook = Look_RightDown;
		}
		else if(m_eLook == Look_Left)
		{
			m_eLook = Look_LeftDown;
		}
	}
	else if(DataMgr->m_pPlayer->getPos().y < getPos().y - 10)
	{
		if(m_eLook == Look_Right)
		{
			m_eLook = Look_RightUp;
		}
		else if(m_eLook == Look_Left)
		{
			m_eLook = Look_LeftUp;
		}
	}

}