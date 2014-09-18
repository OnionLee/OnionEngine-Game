#include "StdAfx.h"
#include "S_Maker.h"
#include "Sprite.h"
#include "Director.h"


S_Maker::S_Maker(void)
{
}


S_Maker::~S_Maker(void)
{
}

bool S_Maker::init()
{
	CSprite * spr = CSprite::create("Resource/Maker/credit.png");
	addChild(spr);
	return true;
}
void S_Maker::update()
{
	if(InputMgr->GetKey(Key_Shot) == Key_Down)
	{
		SceneMgr->NowSceneChange(S_Title);
	}
}
