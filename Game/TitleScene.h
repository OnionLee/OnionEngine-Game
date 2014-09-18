#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Lable.h"
class CTitleScene : public CScene
{
public:
	CTitleScene(void);
	~CTitleScene(void);

	virtual bool init();
	virtual void update();

	CSprite * m_pForeGround;
	CSprite * m_pBackGround;
	CSprite * m_pPangPare;
	CSprite * m_pButtons[5];

	int m_nSelcnum;
	int m_nSceneCount;

	void menuUpdate();
	void buttonUpdate();
	void pangUpdate();
	


	MAKE_CREATE(CTitleScene);
};

