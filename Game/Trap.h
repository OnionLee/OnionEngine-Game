#pragma once

#include "Box.h"

class CTrap : public CBox
{
public:
	CTrap(void);
	~CTrap(void);

	virtual bool init();
	virtual void update();

	int m_nAttackTime;
	bool m_isAttacking;

	void Attacking();
	virtual void Attacked(int Power);

	static CTrap * craete();
};

