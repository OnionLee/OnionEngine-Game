#include "StdAfx.h"
#include "ItemBox.h"


CItemBox::CItemBox(void)
{
}


CItemBox::~CItemBox(void)
{
}


bool CItemBox::init(ItemIndex index)
{
	m_eIndex = index;

	switch(m_eIndex)
	{
	case ItemGrenade:
		CSprite::init("Resource/Item/grenade.png");
		break;
	case ItemMultiple:
		CSprite::init("Resource/Item/multi.png");
		break;
	case ItemBigMulti:
		CSprite::init("Resource/Item/bigmulti.png");
		break;
	case ItemBomb:
		CSprite::init("Resource/Item/bomb.png");
		break;
	case ItemSuper:
		CSprite::init("Resource/Item/super.png");
		break;
	case ItemLife:
		CSprite::init("Resource/Item/life.png");
		break;
	}

	setAcp(ccp(0,0));


	return true;
}

CItemBox * CItemBox::create(ItemIndex index)
{
	CItemBox * temp = new CItemBox();
	temp->init(index);

	return temp;
}
