#include "StdAfx.h"
#include "DataManager.h"
#include "resource.h"
#include "Director.h"


CDataManager::CDataManager(void)
{
	m_WeaponIndex = Weapon_Nomal;
	//���� ��ź ����
	m_nGrenade = 3;
	//���� ü��
	m_nHp = 100;
	//���� ���ھ� ����
	m_nScore = 0;
	//������ ������
	m_nRank = 0;
	
	m_isActive = true;
}


CDataManager::~CDataManager(void)
{
}

void CDataManager::statgeReset()
{
	m_WeaponIndex = Weapon_Nomal;
	//���� ��ź ����
	m_nGrenade = 3;
	//���� ü��
	m_nHp = 100;
	//���� ���ھ� ����
	m_nScore = 0;
	//������ ������
	m_nRank = 0;
	
	m_isActive = true;
}


//�������� �ٲ� �� �������
void CDataManager::setPlayer(CPlayer * player)
{
	m_pPlayer = player;
	m_pPlayer->m_nHp = m_nHp;
	m_pPlayer->m_nGrenade = m_nGrenade;
	m_pPlayer->m_eNomallWeaponState = m_WeaponIndex;

}

void CDataManager::stageUpdate()
{
	m_nGrenade = m_pPlayer->m_nGrenade;
	m_nHp = m_pPlayer->m_nHp;
}

void CDataManager::setScore(int adder)
{
	m_nScore+=adder;
}

void CDataManager::setName(const char * name)
{
	m_sName = name;
}

void CDataManager::init()
{
	
}

BOOL CALLBACK DIGACTIVE(HWND hDig, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDig, LOWORD(wParam));
			char buf[32];
			GetDlgItemText(hDig,IDC_GAME,buf,32);
			DataMgr->setName(buf);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}