#include "StdAfx.h"
#include "S_Ending.h"
#include "Director.h"


S_Ending::S_Ending(void)
{
}


S_Ending::~S_Ending(void)
{
}


bool S_Ending::init()
{
	spr = CSprite::create("Resource/Ending/End.png");
	spr->setPos(ccp(0,-704));
	addChild(spr);
	return true;
}
void S_Ending::update()
{
	if(0 > spr->getPos().y)
		spr->setPos(ccp(0,spr->getPos().y + 1));
	else
		SceneMgr->NowSceneChange(S_Title);
		
}