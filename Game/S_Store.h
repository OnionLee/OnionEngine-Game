#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Lable.h"

class BuyButton : public CNode
{
public:
	CSprite * m_pSButton;
	CSprite * m_pXButton;
	CLable * m_pConstLable;
	int m_nCost;
	
	virtual bool init()
	{
		m_pSButton = CSprite::create("Resource/Store/SButton.png");
		m_pSButton->setAcp(ccp(0.5,0.5));
		m_pXButton = CSprite::create("Resource/Store/XButton.png");
		m_pXButton->setAcp(ccp(0.5,0.5));
		m_pConstLable = CLable::create("½Å¸íÁ¶");

		m_pConstLable->setAcp(ccp(0.5,0.5));
		m_pConstLable->setText("");
		m_pConstLable->setPos(ccp(0,125));
		m_pConstLable->setSiz(ccp(0.5f,0.5f));


		m_nCost = 0;
		addChild(m_pSButton);
		addChild(m_pXButton);
		addChild(m_pConstLable);

		return true;
	}

	MAKE_CREATE(BuyButton);
};

class S_Store : public CScene
{
public:
	S_Store(void);
	~S_Store(void);

	int m_nNowMoney;
	int m_nShowMoney;
	int m_nSelect;

	BuyButton * m_pButtons[3];
	CLable * m_pConstLable;

	virtual bool init();
	virtual void update();

	MAKE_CREATE(S_Store);
};

