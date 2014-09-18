#include "StdAfx.h"
#include "Animation.h"
#include "Director.h"



CAnimation::CAnimation(void)
{
	m_isLoop = false;
	m_isLoopEnd = false;


	m_nFrameSize = 0;

	m_nFrameRate = 0;

	m_nCurTickTime = 0;

	m_nCurFrameCount = 0;
}


CAnimation::~CAnimation(void)
{
	for(int i = 0; i<m_vFrames.size(); i++)
	{
		delete m_vFrames[i];
	}

	m_vFrames.clear();

}

void CAnimation::init(int FrameRate, bool Loop)
{
	m_nFrameRate = FrameRate;
	m_isLoop = Loop;
	m_isLoopEnd = true;
}
void CAnimation::addFrame(const char * filename)
{
	CTexture2D * temp = new CTexture2D();
	temp->LoadFromFile(filename);
	m_vFrames.push_back(temp);
	m_nFrameSize++;
}

CTexture2D * CAnimation::run()
{
	CTexture2D * value = LOOPACTIVE;

	if(m_isLoopEnd)
	{

		m_nCurTickTime += TimeMgr->m_nDetaTime;

		//시간이 지났을때
		if(m_nCurTickTime>m_nFrameRate)
		{
			value = m_vFrames[m_nCurFrameCount];
			m_nCurFrameCount++;
			m_nCurTickTime = 0;

			if(m_nCurFrameCount>=m_nFrameSize)
			{
				if(m_isLoop)
					m_nCurFrameCount = 0;
				else
					m_isLoopEnd = false;
			}
		}
		else
		{
			value = LOOPACTIVE;
		}
	}
	else
	{
		value = LOOPEND;
	}
	return value;
}
