#include "StdAfx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager(void)
{
	m_nOldTime = 0;
	m_nCurTick = 0;
	m_nCurFrame = 0;
	m_nDetaTime = 0;

	FPS = 0;
}


CTimeManager::~CTimeManager(void)
{
}


void CTimeManager::init()
{
	m_nOldTime = GetTickCount();
}
void CTimeManager::update()
{
	int Curtime = GetTickCount();
	m_nDetaTime = Curtime - m_nOldTime;
	m_nOldTime = Curtime;

	
	m_nCurTick+= m_nDetaTime;
	m_nCurFrame++;
	
	float secound = (float)((float)m_nCurTick/1000.0f);
	FPS = (float)((float)m_nCurFrame/secound);

	printf("FPS : %.2f\n",FPS);
}