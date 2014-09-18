#include "StdAfx.h"
#include "InputManager.h"




CInputManager::CInputManager(void)
{
}


CInputManager::~CInputManager(void)
{
}

void CInputManager::init()
{
	int keyArray[] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Z','X','C','Q'};
	for(int i = 0; i<8; i++)
	{
		m_pKeyInfo[i].KeyCode = keyArray[i];
		m_pKeyInfo[i].m_eKeyState = KeyState::sKey_Null;
	}
}

void CInputManager::update()
{
	for(int i = 0; i<8; i++)
	{
		if(GetAsyncKeyState(m_pKeyInfo[i].KeyCode))
		{
			if(m_pKeyInfo[i].m_eKeyState == KeyState::sKey_Null)
			{
				m_pKeyInfo[i].m_eKeyState = KeyState::sKey_Down;
			}
			else if(m_pKeyInfo[i].m_eKeyState == KeyState::sKey_Down)
			{
				m_pKeyInfo[i].m_eKeyState = KeyState::sKey_Push;
			}
		}
		else
		{
			if(m_pKeyInfo[i].m_eKeyState == KeyState::sKey_Push)
			{
				m_pKeyInfo[i].m_eKeyState = KeyState::sKey_Up;
			}
			else if(m_pKeyInfo[i].m_eKeyState == KeyState::sKey_Up)
			{
				m_pKeyInfo[i].m_eKeyState = KeyState::sKey_Null;
			}
		}
	}
}