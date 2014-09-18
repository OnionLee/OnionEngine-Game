#include "StdAfx.h"
#include "S_HowToPlay.h"
#include "Director.h"


S_HowToPlay::S_HowToPlay(void)
{
}


S_HowToPlay::~S_HowToPlay(void)
{
}

bool S_HowToPlay::init()
{
	CSprite * spr = CSprite::create("Resource/H2P/how_to_play.png");
	addChild(spr);
	return true;
}
void S_HowToPlay::update()
{

	if(InputMgr->GetKey(Key_Shot) == sKey_Down)
	{
		SceneMgr->NowSceneChange(S_Title);
	}
}
