#pragma once
class CTimeManager
{
public:
	CTimeManager(void);
	~CTimeManager(void);
	
	void init();
	void update();

	int m_nOldTime;
	int m_nCurTick;
	int m_nCurFrame;
	int m_nDetaTime;

	float FPS;

};

