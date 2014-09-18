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

	//������ ������
	int m_nFrameSize;
	//������ ����
	int m_nFrameRate;
	//���� ���� �ð�
	int m_nCurTickTime;
	//���� ���� ī��Ʈ
	int m_nCurFrameCount;

	void init(int FrameRate, bool Loop);
	void addFrame(const char * filename);
	CTexture2D * run();

	std::vector<CTexture2D *> m_vFrames;
};

