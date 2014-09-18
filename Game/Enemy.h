#pragma once
#include "BaseChar.h"

enum aiState{
	ai_Idel,
	ai_Walk,
	ai_Shot,
	ai_Null,
};

class CEnemy : public CBaseChar
{
public:
	CEnemy(void);
	~CEnemy(void);

	static CEnemy * create(CharIndex index);
	
	virtual bool init(CharIndex index);
	virtual void update();

	void aiUpdate();

	void stateChange();

	void shotState();

	void lookState();

	int m_nShotTime;

	int m_naiStateTime;

	int m_naiNextTime;

	aiState m_eAiState;
};

