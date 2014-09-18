#include "StdAfx.h"
#include "S_Rank.h"
#include "Director.h"

S_Rank::S_Rank(void)
{
}


S_Rank::~S_Rank(void)
{
}



bool S_Rank::init()
{


	auto spr2 = CSprite::create("Resource/Rank/Back.png");
	addChild(spr2);

	auto spr = CSprite::create("Resource/Rank/Rank.png");
	addChild(spr);

	for(int i = 0 ; i<5; i++)
	{
		RankStruct temp;
		temp.Name = "-";
		temp.Score = 0;
		m_vRank.push_back(temp);
	}

	FILE * fp;
	fopen_s(&fp, "Resource/Data/rank.txt", "rb" );
	if(fp == 0)
	{

	}
	else
	{
		char buf[32];
		fscanf_s(fp,"%s",buf);
		int Count = atoi(buf);
		for(int i =0; i<Count; i++)
		{
			RankStruct temp;
			fscanf_s(fp,"%s\n",buf);
			temp.Score = atoi(buf);
			fscanf_s(fp,"%s\n",buf);
			temp.Name = buf;
			m_vRank.push_back(temp);
		}
		fclose(fp);
	}

	
	if(DataMgr->m_nScore > 0)
	{
		RankStruct temp;
		temp.Name = DataMgr->m_sName;
		temp.Score = DataMgr->m_nScore;
		m_vRank.push_back(temp);
	}

	std::sort(m_vRank.begin(),m_vRank.end(),sort);

	FILE * fp2;
	fopen_s(&fp2,"Resource/Data/rank.txt", "w");
	fprintf(fp2,"%d\n",5);
	for(int i = 0; i<5; i++)
	{
		fprintf(fp2,"%d\n",m_vRank[i].Score);
		fprintf(fp2,"%s\n",m_vRank[i].Name.c_str());
		
		char buf[64];
		sprintf_s(buf,"%d",i+1);
		m_pLaRank[i] = CLable::create("신명조");
		m_pLaRank[i]->setText(buf);
		m_pLaRank[i]->setPos(ccp(290,330 + (i*120)));
		addChild(m_pLaRank[i]);

		sprintf_s(buf, "%s", m_vRank[i].Name.c_str());
		m_pLaScore[i] = CLable::create("신명조");
		m_pLaScore[i]->setText(buf);
		m_pLaScore[i]->setPos(ccp(370,330 + (i*120)));
		addChild(m_pLaScore[i]);

		sprintf_s(buf, "%d", m_vRank[i].Score);
		m_pLaName[i] = CLable::create("신명조");
		m_pLaName[i]->setText(buf);
		m_pLaName[i]->setPos(ccp(670,330 + (i*120)));
		addChild(m_pLaName[i]);
	}
	fclose(fp2);

	return true;
}
void S_Rank::update()
{
	CScene::update();
	static int i = 0;
	i+= 16;
	if(i>1000)
		if(InputMgr->GetKey(Key_Shot) == Key_Down)
		{
			SceneMgr->NowSceneChange(S_Title);
		}
}

bool sort (RankStruct a, RankStruct b)
{
	return a.Score > b.Score;
}
