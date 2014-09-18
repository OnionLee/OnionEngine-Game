#include "StdAfx.h"
#include "Player.h"
#include "Director.h"


CPlayer::CPlayer(void)
{
	m_nGrenade = 0;
	m_nShotTime = 0;
	m_nSuperCount = 0;
	isWating = false;
	isGrenade = false;
	isSuper = false;
}


CPlayer::~CPlayer(void)
{
}


bool CPlayer::init()
{
	if(!CBaseChar::init(Index_Player))
		return false;

	//±âº»ÃÑ ¼³Á¤
	m_eNomallWeaponState = Weapon_Nomal;

	//ÇöÀç ÃÑ ¼³Á¤
	m_eNowWeapon = m_eNomallWeaponState;

	m_nGrenade = 3;

	return true;
}

void CPlayer::update()
{
	fireWating();
	CBaseChar::update();
	inputUpdate();
	superUpdate();


}

void CPlayer::inputUpdate()
{
	if(InputMgr->GetKey(Key_Left) == sKey_Push||
		InputMgr->GetKey(Key_Left) == sKey_Down)
	{	//¿ÞÂÊ + À­ÂÊ
		if(InputMgr->GetKey(Key_Up) == sKey_Push||
			InputMgr->GetKey(Key_Up) == sKey_Down)	
		{
			m_eLook = Look_LeftUp;
		}
		//¿ÞÂÊ + ¾Æ·§ÂÊ
		else if(InputMgr->GetKey(Key_Down) == sKey_Push||
			InputMgr->GetKey(Key_Down) == sKey_Down)
		{
			m_eLook = Look_LeftDown;
		}
		//¿ÞÂÊ
		else
		{
			m_eLook = Look_Left;
		}
		m_eState = State_Run;
	}
	else if(InputMgr->GetKey(Ket_Right) == sKey_Push||
		InputMgr->GetKey(Ket_Right) == sKey_Down)
	{
		//¿À¸¥ÂÊ + À§ÂÊ
		if(InputMgr->GetKey(Key_Up) == sKey_Push||
			InputMgr->GetKey(Key_Up) == sKey_Down)
		{
			m_eLook = Look_RightUp;
		}
		//¿À¸¥ÂÊ + ¾Æ·§ÂÊ
		else if(InputMgr->GetKey(Key_Down) == sKey_Push||
			InputMgr->GetKey(Key_Down) == sKey_Down)
		{
			m_eLook = Look_RightDown;
		}
		//¿À¸¥ÂÊ
		else
		{
			m_eLook = Look_Right;
		}
		m_eState = State_Run;
	}
	//À§ÂÊ
	else if(InputMgr->GetKey(Key_Up) == sKey_Push||
		InputMgr->GetKey(Key_Up) == sKey_Down)
	{
		m_eLook = Look_Up;
		m_eState = State_Idel;
	}
	//¾Æ·§ÂÊ
	else if(InputMgr->GetKey(Key_Down) == sKey_Push||
		InputMgr->GetKey(Key_Down) == sKey_Down)
	{
		m_eLook = Look_Down;
		m_eState = State_Idel;
	}
	else
	{
		if(getSiz().x == -1)
		{
			m_eLook = Look_Right;
		}
		else
		{
			m_eLook = Look_Left;
		}
		m_eState = State_Idel;
	}

	if(InputMgr->GetKey(Key_Jump) == sKey_Down && m_eCollider!= Coll_Air)
	{
		m_eCollider = Coll_Jump;
	}

	if(InputMgr->GetKey(Key_Shot) == sKey_Down)
	{
		if(!isWating)
		{
			m_isFire = true;
			isWating = true;
		}
	}

	if(InputMgr->GetKey(Key_Shot) == sKey_Push)
	{
		if(m_eNowWeapon == Weapon_Multiple||
			m_eNowWeapon == Weapon_BigMulti)
		if(!isWating)
		{
			m_isFire = true;
			isWating = true;
		}
	}

	if(InputMgr->GetKey(Key_Shot) == sKey_Up)
	{
		m_isFire = false;
	}



	if(InputMgr->GetKey(Key_Grenade) == sKey_Down)
	{
		if(m_nGrenade >0)
		{
			m_nGrenade -= 1;
			isGrenade = true;
		}
	}
	else
	{
		isGrenade = false;
	}

	if(InputMgr->GetKey(Key_Cheat) == sKey_Down)
	{
		isSuper = true;
	}

}

void CPlayer::fireWating()
{
	if(isWating)
	{
		m_isFire = false;
		m_nShotTime+=16;
		if(m_nShotTime>100)
		{
			isWating = false;
			m_nShotTime = 0;
		}
	}
}

void CPlayer::setWeapon(CharWeapon index)
{
	m_eNowWeapon = index;

	switch(m_eNowWeapon)
	{
	case Weapon_Nomal:
		m_pArm->setTex(TexMgr->LoadTexture("Resource/Char/Player/handgun_1.png"));
		break;
	case Weapon_Double:
		m_pArm->setTex(TexMgr->LoadTexture("Resource/Char/Player/handgun_2.png"));
		break;
	case Weapon_Tripel:
		m_pArm->setTex(TexMgr->LoadTexture("Resource/Char/Player/handgun_3.png"));
		break;
	case Weapon_Multiple:
		m_pArm->setTex(TexMgr->LoadTexture("Resource/Char/Player/itemgun_1.png"));
		break;
	case Weapon_BigMulti:
		m_pArm->setTex(TexMgr->LoadTexture("Resource/Char/Player/itemgun_2.png"));
		break;
	}

}

void CPlayer::superUpdate()
{

	if(isSuper)
	{
		m_nSuperCount += 16;

		m_pBody->setCor(ccc4(100,50,50,255));
		m_pArm->setCor(ccc4(100,50,50,255));
		m_nHp = 9999;

		if(m_nSuperCount > 5000)
		{
			m_pBody->setCor(ccc4(255,255,255,255));
			m_pArm->setCor(ccc4(255,255,255,255));
			m_nSuperCount = 0;
			m_nHp = 100;
			isSuper = false;
		}
	}
}