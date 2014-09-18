#pragma once
#include "Scene.h"
#include "Sprite.h"

class S_Ending : public CScene
{
public:
	S_Ending(void);
	~S_Ending(void);

	virtual bool init();
	virtual void update();

	CSprite * spr;

	MAKE_CREATE(S_Ending)
};

