#pragma once
#include "Sprite.h"
#include "Animation.h"

enum BulletState{
	StateB_Life,
	StateB_Crash,
	StateB_Die,
	StateB_Null,
};

enum CBulletIndex{
	Index_Nomal,
	Index_Double,
	Index_Triple,
	Index_Multiple,
	Index_BigMulti,
	Index_Grenade,
};


class CBullet : public CSprite
{
public:
	CBullet(void);
	~CBullet(void);

	BulletState m_eState;
	D3DXVECTOR2 m_vMoveVector;
	CBulletIndex m_eIndex;

	virtual bool init(CBulletIndex index);
	virtual void update();

	virtual void shotbullet(D3DXVECTOR2 pos, D3DXVECTOR2 vector, bool isPlayer = true);

	int m_nLifeTime;

	int m_nSpeed;
	int m_nPower;

	bool m_isPlayerBullet;

	CAnimation * m_pPaticel;

	void aniUpdate();
};

