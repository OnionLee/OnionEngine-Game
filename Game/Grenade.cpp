#include "StdAfx.h"
#include "Grenade.h"


CGrenade::CGrenade(void)
{
	m_fGravity = 0;
}


CGrenade::~CGrenade(void)
{

}

void CGrenade::update()
{
	CBullet::update();

	m_fGravity += GRENADEGRAVITY;

	m_vMoveVector.y += m_fGravity;

	if(m_eState == StateB_Life)
	if(getPos().y>GRENADEGROUND)
	{
		m_eState = StateB_Crash;
	}
}

void CGrenade::shotbullet(D3DXVECTOR2 pos, D3DXVECTOR2 vector, bool isPlayer/* = true*/)
{
	m_eState = StateB_Life;
	float start_x = pos.x;
	float start_y = pos.y;

	setPos(ccp(start_x,start_y));

	m_vMoveVector.x =  cos(60.0 *  3.141592 / 180) * m_nSpeed * vector.x * 2;
	m_vMoveVector.y = -sin(60.0 *  3.140592 / 180) * m_nSpeed;

	m_isPlayerBullet = isPlayer;
}
