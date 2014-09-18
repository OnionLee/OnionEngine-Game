#include "StdAfx.h"
#include "GameScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "UILayer.h"


GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

GameScene * GameScene::createStage1()
{
	GameScene * temp = new GameScene();
	temp->init();
	
	Stage1 * layer2 = Stage1::create();
	UILayer * layer1 = UILayer::create();

	
	temp->addChild(layer2);
	temp->addChild(layer1);

	return temp;
}

GameScene * GameScene::createStage2()
{
	GameScene * temp = new GameScene();
	temp->init();
	UILayer * layer1 = UILayer::create();
	Stage2 * layer2 = Stage2::create();

	
	temp->addChild(layer2);
	temp->addChild(layer1);

	return temp;
}