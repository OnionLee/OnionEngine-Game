#pragma once
#include "Layer.h"
#include "Sprite.h"
#include "Lable.h"

class UILayer : public CLayer
{
public:
	UILayer(void);
	~UILayer(void);

	virtual bool init();
	virtual void update();

	CLable * m_pHpLable;
	CLable * m_pGrenadeLabel;
	CLable * m_pScoreLabel;
	CLable * m_pNameLabel;

	CSprite * m_pPanal;

	CLable * m_pRestartLable;

	int m_nRestratCount;
	int m_nTickCount;
	void reStartUpdate();

	CSprite * m_pDie;


	MAKE_CREATE(UILayer);


};

