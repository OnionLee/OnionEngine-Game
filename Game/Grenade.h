#pragma once
#include "Bullet.h"

#define GRENADEGRAVITY 0.02
#define GRENADEGROUND 875

class CGrenade : public CBullet
{
public:
	CGrenade(void);
	~CGrenade(void);

	virtual void update();

	virtual void shotbullet(D3DXVECTOR2 pos, D3DXVECTOR2 vector, bool isPlayer = true);

	float m_fGravity;
};

