#pragma once
#include "Sprite.h"

enum ItemIndex{
	ItemGrenade,
	ItemMultiple,
	ItemBigMulti,
	ItemBomb,
	ItemSuper,
	ItemLife,
};

class CItemBox : public CSprite
{
public:
	CItemBox(void);
	~CItemBox(void);

	ItemIndex m_eIndex;

	virtual bool init(ItemIndex index);

	static CItemBox * create(ItemIndex index);
};

