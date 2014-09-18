#pragma once
#include "BaseChar.h"


class CPlayer : public CBaseChar
{
public:
	CPlayer(void);
	~CPlayer(void);

	virtual bool init();
	virtual void update();

	CharWeapon m_eNomallWeaponState;
	//ÇöÀç ÆøÅº °³¼ö
	int m_nGrenade;

	void inputUpdate();

	MAKE_CREATE(CPlayer);

	int m_nShotTime;
	bool isWating;
	bool isGrenade;
	void fireWating();
	void setWeapon(CharWeapon index);

	bool isSuper;
	void superUpdate();
	int m_nSuperCount;
};

