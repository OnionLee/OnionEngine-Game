#pragma once
class CSoundManager
{
public:
	CSoundManager(void);
	~CSoundManager(void);

	void PlayerSound(const char * filename, bool isMp3, int index);
};

