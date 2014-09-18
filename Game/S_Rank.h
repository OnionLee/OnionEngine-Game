#pragma once
#include "Scene.h"
#include "Lable.h"

struct RankStruct{
	std::string Name;
	int Score;
};

class S_Rank : public CScene
{
public:
	S_Rank(void);
	~S_Rank(void);

	CLable * m_pLaRank[5];
	CLable * m_pLaScore[5];
	CLable * m_pLaName[5];

	std::vector<RankStruct> m_vRank;

	virtual bool init();
	virtual void update();

	MAKE_CREATE(S_Rank);
};

bool sort (RankStruct a, RankStruct b);
