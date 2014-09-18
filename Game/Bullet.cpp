#include "StdAfx.h"
#include "Bullet.h"
#include "Director.h"


CBullet::CBullet(void)
{
	m_nSpeed = 0;
	m_nPower = 0;
	m_nLifeTime = 0;
	m_eState = StateB_Null;
	m_isPlayerBullet = false;

	m_vMoveVector = ccp(0,0);
}


CBullet::~CBullet(void)
{
}

bool CBullet::init(CBulletIndex index)
{
	m_pPaticel = new CAnimation();
	m_pPaticel->init(100,false);
	m_eIndex = index;

	switch(m_eIndex)
	{
	case Index_Nomal:
		CSprite::init("Resource/Bullet/Bullet1.png");
		m_nSpeed = 15;
		m_nPower = 3;
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_0.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_1.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_3.png");
		break;
	case Index_Double:
		CSprite::init("Resource/Bullet/Bullet2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_0.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_1.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_3.png");
		m_nSpeed = 14;
		m_nPower = 3;
		break;
	case Index_Triple:
		CSprite::init("Resource/Bullet/Bullet3.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_0.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_1.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_3.png");
		m_nSpeed = 13;
		m_nPower = 3;
		break;
	case Index_Multiple:
		CSprite::init("Resource/Bullet/Bullet4.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_0.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_1.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_3.png");
		m_nSpeed = 12;
		m_nPower = 3;
		break;
	case Index_BigMulti:
		CSprite::init("Resource/Bullet/Bullet4.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_0.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_1.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_2.png");
		m_pPaticel->addFrame("Resource/Bullet/Bullet_Paticle_3.png");
		m_nSpeed = 11;
		m_nPower = 6;
		this->setSiz(ccp(2,2));
		break;
	case Index_Grenade:
		CSprite::init("Resource/Bullet/Grenade.png");
		m_pPaticel->addFrame("Resource/Bullet/bang_0.png");
		m_pPaticel->addFrame("Resource/Bullet/bang_1.png");
		m_pPaticel->addFrame("Resource/Bullet/bang_2.png");
		m_pPaticel->addFrame("Resource/Bullet/bang_3.png");
		m_nSpeed = 10;
		m_nPower = 10;
		break;
	}

	setAcp(ccp(0.5,0.5));
	setBoundBox();

	return true;
}

void CBullet::shotbullet(D3DXVECTOR2 pos, D3DXVECTOR2 vector, bool isPlayer)
{
	m_eState = StateB_Life;
	float start_x = pos.x + ( cos(atan2(vector.y,vector.x)) * 100);
	float start_y = pos.y + (-sin(atan2(vector.y,vector.x)) * 100);

	setPos(ccp(start_x,start_y));

	m_vMoveVector.x = ( cos(atan2(vector.y,vector.x)) * m_nSpeed);
	m_vMoveVector.y = (-sin(atan2(vector.y,vector.x)) * m_nSpeed);

	m_isPlayerBullet = isPlayer;
}


void CBullet::update()
{
	switch(m_eState)
	{
	case StateB_Life:
		setPos(ccp(getPos().x + m_vMoveVector.x ,getPos().y + m_vMoveVector.y));

		if(m_eIndex != Index_Grenade)
		{
			m_nLifeTime += TimeMgr->m_nDetaTime;
			if(m_nLifeTime > 1000)
			{
				m_eState = StateB_Crash;
				m_nLifeTime = 0;
			}
		}
		break;
		//현재 임시로 지정해둔 스테이트
	case StateB_Crash:
		m_eState = StateB_Die;
		break;
	case StateB_Die:
		aniUpdate();
		break;
	}


}

void CBullet::aniUpdate()
{
	auto temp = m_pPaticel->run();
	if(temp == LOOPACTIVE)
		return;

	if(temp == LOOPEND)
	{
		m_eState = StateB_Null;
		return;
	}

	setTex(temp);
	setRect(temp->m_rRect);
	if(m_eIndex != Index_Grenade)
		setAcp(ccp(0.5,0.5));
	else
		setAcp(ccp(0.5,1));

}