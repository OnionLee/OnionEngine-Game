#pragma once
#include "Node.h"
#include "Sprite.h"
#include "Lable.h"
#include "Animation.h"

#define CHARGRAVITY 0.05f
#define GROUNDPOS 800
#define BOXPOS 577
#define JUMPPOWER 20


//������ ����
enum CharState{
	State_Idel,
	State_Run,
	State_Die,
	State_Null,
};

//�浹����
enum CharCollider{
	Coll_Air,
	Coll_Ground,
	Coll_Jump,
	Coll_Box,
};

//�ü�����
enum CharLook{
	Look_Up,
	Look_RightUp,
	Look_Right,
	Look_RightDown,
	Look_Down,
	Look_LeftDown,
	Look_Left,
	Look_LeftUp,
};

//�������
enum CharWeapon{
	Weapon_Nomal,
	Weapon_Double,
	Weapon_Tripel,
	Weapon_Multiple,
	Weapon_BigMulti,
	Weapon_Grenade,
};

//����
enum CharIndex{
	Index_Player,
	Index_Enemy1,
	Index_Enemy2,
	Index_Boss1,
	Index_Boss2,
};

class CBaseChar : public CNode
{
public:
	CBaseChar(void);
	~CBaseChar(void);

	//����� �α�
	CLable * DebugInfo;

	//���µ�
	CharState m_eState;
	CharCollider m_eCollider;
	CharLook m_eLook;
	CharWeapon m_eNowWeapon;
	CharIndex m_eCharIndex;

	//������Ʈ ��ȯ �����
	CharState m_eOldState;

	//������
	CSprite * m_pBody;
	CSprite * m_pArm;

	//���� �ִϸ��̼�
	CAnimation * m_pNowAni;
	//�ִϸ��̼� ���µ�
	CAnimation * m_pIdel;
	CAnimation * m_pWalk;
	CAnimation * m_pDie;

	//�� �߻�
	bool m_isFire;

	//���� ������ �߷�
	float m_faddGrivity;

	//���� �̵�����
	D3DXVECTOR2 m_vMoveVector; 

	//���� �ѱ⺤��
	D3DXVECTOR2 m_vWeaponVector;

	//�⺻ ü��
	int m_nHp;
	//���� ü��
	int m_nCurHp;

	//�⺻ �ӷ�
	int m_nSpeed;
	//���� �ӷ�
	int m_nCurSpeed;

	virtual bool init(CharIndex index);
	virtual void update();
	virtual void release();

	//���� ������Ʈ��
	void stateUpdate();
	void aniUpdate();
	void colliderUpdate();
	void lookUpdate();
	void weaponUpdate();

	//���Ͱ� ����
	void moveUpdate();

	//ĳ���� �����Լ�
	void makeChar(const char * playerName, int x, int y);
	CAnimation * makeAnimation(const char * charpath, const char * aniname, bool loop, int count);

	//���� ��������
	void Attacked(int Power);
	//���� ���ݴ��ϰ� �ִ���
	//���ݴ��ϸ� true���ǰ� �����ð����� ���� �ٲ��.
	void attackUpdate();
	bool m_isAttacking;
	//���� �������� �� �󸶵��� ��ȯ�Ұ���
	int m_nAttackTime;

	//�״� �ִϸ��̼�
	void dieAnimation();
	int m_nDieAniTime;

	float m_fNowAlpha;




};

