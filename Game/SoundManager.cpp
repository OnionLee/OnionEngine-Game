#include "StdAfx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager(void)
{
}


CSoundManager::~CSoundManager(void)
{
}

void CSoundManager::PlayerSound(const char * filename, bool isMp3, int index)
{
	char buf[256];
	if(isMp3)
	{
		sprintf_s(buf, "open %s type mpegvideo alias %d", filename, index);
	}
	else
	{
		sprintf_s(buf, "open %s type waveaudio alias %d", filename, index);
	}

	mciSendString(buf,0,0,0);
	sprintf_s(buf,"play %d notify repeat",index);
	mciSendString(buf,0,0,0);
}