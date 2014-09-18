#pragma once
#include "Player.h"
class CDataManager
{
public:
	CDataManager(void);
	~CDataManager(void);

	//���� �÷������� �÷��̾�
	CPlayer * m_pPlayer;
	

	//�������� �ٲ� �� �������
	void setPlayer(CPlayer * player);
	//�������� ������ ���������� ó��
	void stageUpdate();
	//���ھ� �߰�
	void setScore(int adder);
	//�̸� ����
	void setName(const char * name);
	//�̸��޾ƿ�
	void init();
	//�������� �����
	void statgeReset();

	//�÷��̾� ����
	std::string m_sName;
	//���� ��ź ����
	int m_nGrenade;
	//���� ü��
	int m_nHp;
	//���� ���ھ� ����
	int m_nScore;
	//������ ������
	int m_nRank;

	bool m_isActive;

	CharWeapon m_WeaponIndex;
	
};

BOOL CALLBACK DIGACTIVE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

