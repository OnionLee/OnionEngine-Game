#pragma once
#include "Texture2D.h"

#define LOOPEND (CTexture2D *)-2
#define LOOPACTIVE (CTexture2D *)-1

class CAnimation
{
public:
	CAnimation(void);
	~CAnimation(void);

	int m_isLoop;
	int m_isLoopEnd;

	//프레임 사이즈
	int m_nFrameSize;
	//프레임 간격
	int m_nFrameRate;
	//현재 누적 시간
	int m_nCurTickTime;
	//현재 누적 카운트
	int m_nCurFrameCount;

	void init(int FrameRate, bool Loop);
	void addFrame(const char * filename);
	CTexture2D * run();

	std::vector<CTexture2D *> m_vFrames;
};

