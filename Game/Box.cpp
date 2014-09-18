#include "StdAfx.h"
#include "Box.h"


CBox::CBox(void)
{
}


CBox::~CBox(void)
{
}

void CBox::update()
{
	if(m_eState!=BoxNull)
	switch(m_eState)
	{
	case BoxLife:

		break;
	case BoxDie:
		dieAniUpdate();
		break;
	}
}

bool CBox::init()
{
	m_nHp = false;
	m_isOnBox = false;
	m_eState = BoxLife;



	return false;
}

void CBox::dieAniUpdate()
{
	auto temp = m_pDieAni->run();
	if(temp == LOOPACTIVE)
		return;

	if(temp == LOOPEND)
	{
		m_eState = BoxNull;
		return;
	}

	setTex(temp);
}