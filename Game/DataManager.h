#pragma once
#include "Player.h"
class CDataManager
{
public:
	CDataManager(void);
	~CDataManager(void);

	//현재 플레이중인 플레이어
	CPlayer * m_pPlayer;
	

	//스테이지 바뀔때 꼭 해줘야함
	void setPlayer(CPlayer * player);
	//스테이지 내부의 루프문에서 처리
	void stageUpdate();
	//스코어 추가
	void setScore(int adder);
	//이름 설정
	void setName(const char * name);
	//이름받아옴
	void init();
	//스테이지 재실행
	void statgeReset();

	//플레이어 네임
	std::string m_sName;
	//현재 폭탄 개수
	int m_nGrenade;
	//현재 체력
	int m_nHp;
	//현재 스코어 저장
	int m_nScore;
	//쓸지는 미지수
	int m_nRank;

	bool m_isActive;

	CharWeapon m_WeaponIndex;
	
};

BOOL CALLBACK DIGACTIVE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

