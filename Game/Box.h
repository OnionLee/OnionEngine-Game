#pragma once
#include "Sprite.h"
#include "Animation.h"

enum BoxState{
	BoxLife,
	BoxDie,
	BoxNull,
};

enum BoxIndex{
	Box_Trap,
	Box_ConBox,
};

class CBox : public CSprite
{
public:

	CBox(void);
	~CBox(void);

	virtual bool init();
	virtual void update();

	void dieAniUpdate();

	BoxState m_eState;

	int m_nHp;
	bool m_isOnBox;

	virtual void Attacked(int Power){}

	CAnimation * m_pDieAni;

	BoxIndex m_index;

};


