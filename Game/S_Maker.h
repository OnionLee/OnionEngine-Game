#pragma once
#include "Scene.h"
class S_Maker : public CScene
{
public:
	S_Maker(void);
	~S_Maker(void);

	MAKE_CREATE(S_Maker);

	virtual bool init();
	virtual void update();
};

