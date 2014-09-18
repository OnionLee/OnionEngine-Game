#pragma once
#include "Scene.h"
#include "Sprite.h"

class OpeningScene : public CScene
{
public:
	virtual bool init();
	virtual void update();
	
	bool m_isOp1;
	bool m_isOp2;
	bool m_isOp3;

	CSprite * m_pOp1;
	CSprite * m_pOp2;
	CSprite * m_pOp3;

	MAKE_CREATE(OpeningScene);

	OpeningScene(void);
	~OpeningScene(void);
};

