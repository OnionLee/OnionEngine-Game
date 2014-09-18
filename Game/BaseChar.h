#pragma once
#include "Node.h"
#include "Sprite.h"
#include "Lable.h"
#include "Animation.h"

#define CHARGRAVITY 0.05f
#define GROUNDPOS 800
#define BOXPOS 577
#define JUMPPOWER 20


//움직임 상태
enum CharState{
	State_Idel,
	State_Run,
	State_Die,
	State_Null,
};

//충돌상태
enum CharCollider{
	Coll_Air,
	Coll_Ground,
	Coll_Jump,
	Coll_Box,
};

//시선상태
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

//무기상태
enum CharWeapon{
	Weapon_Nomal,
	Weapon_Double,
	Weapon_Tripel,
	Weapon_Multiple,
	Weapon_BigMulti,
	Weapon_Grenade,
};

//종류
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

	//디버그 로그
	CLable * DebugInfo;

	//상태들
	CharState m_eState;
	CharCollider m_eCollider;
	CharLook m_eLook;
	CharWeapon m_eNowWeapon;
	CharIndex m_eCharIndex;

	//스테이트 전환 검출용
	CharState m_eOldState;

	//파츠들
	CSprite * m_pBody;
	CSprite * m_pArm;

	//현재 애니메이션
	CAnimation * m_pNowAni;
	//애니메이션 상태들
	CAnimation * m_pIdel;
	CAnimation * m_pWalk;
	CAnimation * m_pDie;

	//총 발사
	bool m_isFire;

	//현재 누적된 중력
	float m_faddGrivity;

	//현재 이동벡터
	D3DXVECTOR2 m_vMoveVector; 

	//현재 총기벡터
	D3DXVECTOR2 m_vWeaponVector;

	//기본 체력
	int m_nHp;
	//현재 체력
	int m_nCurHp;

	//기본 속력
	int m_nSpeed;
	//현재 속력
	int m_nCurSpeed;

	virtual bool init(CharIndex index);
	virtual void update();
	virtual void release();

	//상태 업데이트들
	void stateUpdate();
	void aniUpdate();
	void colliderUpdate();
	void lookUpdate();
	void weaponUpdate();

	//벡터값 변경
	void moveUpdate();

	//캐릭터 생성함수
	void makeChar(const char * playerName, int x, int y);
	CAnimation * makeAnimation(const char * charpath, const char * aniname, bool loop, int count);

	//공격 당했을때
	void Attacked(int Power);
	//현재 공격당하고 있는지
	//공격당하면 true가되고 일정시간동안 색이 바뀐다.
	void attackUpdate();
	bool m_isAttacking;
	//공격 당했을때 색 얼마동안 변환할건지
	int m_nAttackTime;

	//죽는 애니메이션
	void dieAnimation();
	int m_nDieAniTime;

	float m_fNowAlpha;




};

