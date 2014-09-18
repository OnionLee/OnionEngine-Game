#pragma once

enum KeyIndex{
	Key_Up,
	Key_Down,
	Key_Left,
	Ket_Right,
	Key_Shot,
	Key_Jump,
	Key_Grenade,
	Key_Cheat,
};

enum KeyState{
	sKey_Up,
	sKey_Down,
	sKey_Push,
	sKey_Null,
};

struct KeyInfo{
	KeyState m_eKeyState;
	int KeyCode;
};


class CInputManager
{
public:
	CInputManager(void);
	~CInputManager(void);

	KeyInfo m_pKeyInfo[8];

	void init();
	void update();

	KeyState GetKey(KeyIndex index){return m_pKeyInfo[(int)index].m_eKeyState;}
};

