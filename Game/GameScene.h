#pragma once
#include "Scene.h"

class GameScene : public CScene
{
public:
	GameScene(void);
	~GameScene(void);

	static GameScene * createStage1();
	static GameScene * createStage2();
};

