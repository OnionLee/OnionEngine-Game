#pragma once
#include "Scene.h"
class S_HowToPlay : public CScene
{
public:
	S_HowToPlay(void);
	~S_HowToPlay(void);

	MAKE_CREATE(S_HowToPlay);

	virtual bool init();
	virtual void update();
};

