#include "StdAfx.h"
#include "BaseChar.h"
#include "Director.h"



CBaseChar::CBaseChar(void)
{
	//디버그 로그
	DebugInfo = 0;

	//상태들
	m_eState = m_eOldState = State_Idel;

	m_eCollider = Coll_Air;
	m_eLook = (CharLook)-1;
	m_eNowWeapon = (CharWeapon)-1;
	m_eCharIndex = (CharIndex)-1;

	//파츠들
	m_pBody = 0;
	m_pArm = 0;

	//현재 애니메이션
	m_pNowAni = 0;
	//애니메이션 상태들
	m_pIdel = 0;
	m_pWalk = 0;
	m_pDie = 0;

	//총 발사
	m_isFire = false;

	m_faddGrivity = 0;

	m_vMoveVector = ccp(0,0);
	m_vWeaponVector = ccp(0,0);

	m_nHp = 0;
	m_nCurHp = 0;

	m_nSpeed = 0;
	m_nCurSpeed = 0;

	m_nAttackTime = 0;
	m_isAttacking = false;
	m_nDieAniTime = 0;
	m_fNowAlpha = 255;


}


CBaseChar::~CBaseChar(void)
{
}

bool CBaseChar::init(CharIndex index)
{
	m_eCharIndex = index;

	switch(m_eCharIndex)
	{
	case Index_Player:
		m_eNowWeapon = Weapon_Nomal;
		m_eLook = Look_Right;
		makeChar("Player",40,20);
		m_pNowAni = m_pIdel;
		m_nCurHp = m_nHp = 100;
		m_nSpeed = 3;
		break;
	case Index_Enemy1:
		m_eNowWeapon = Weapon_Nomal;
		m_eLook = Look_Right;
		makeChar("Enemy1",40,10);
		m_pNowAni = m_pIdel;
		m_nCurHp = m_nHp = 6;
		m_nSpeed = 2;
		break;
	case Index_Enemy2:
		m_eNowWeapon = Weapon_Double;
		m_eLook = Look_Right;
		makeChar("Enemy2",40,20);
		m_pNowAni = m_pIdel;
		m_nCurHp = m_nHp = 9;
		m_nSpeed = 1;
		break;
	case Index_Boss1:
		m_eNowWeapon = Weapon_Multiple;
		m_eLook = Look_Right;
		makeChar("Boss1",40,20);
		m_pNowAni = m_pIdel;
		m_nCurHp = m_nHp = 100;
		m_nSpeed = 3;
		break;
	case Index_Boss2:
		m_eNowWeapon = Weapon_BigMulti;
		m_eLook = Look_Right;
		makeChar("Boss2",40,20);
		m_pNowAni = m_pIdel;
		m_nCurHp = m_nHp = 200;
		m_nSpeed = 3;
		break;
	}

	return true;
}
void CBaseChar::update()
{
	//중력 계산
	colliderUpdate();
	//보는것 계산
	lookUpdate();
	//애니움직임
	aniUpdate();
	//스테이트로 움직임
	stateUpdate();
	//최종 벡터 연산
	moveUpdate();

	//무기 발사
	weaponUpdate();

	attackUpdate();

}
void CBaseChar::release()
{
	for(int i = 0; i<m_pNowAni->m_nFrameSize; i++)
	{
		if(m_pNowAni->m_vFrames[i] == m_pBody->getTex())
		{
			m_pNowAni->m_vFrames[i] = 0;
		}
	}
	m_pNowAni = 0;
	delete m_pIdel;
	delete m_pWalk;
	delete m_pDie;

	CNode::release();
}

//상태 업데이트들
void CBaseChar::stateUpdate()
{
	switch(m_eState)
	{
	case State_Idel:
		m_nCurSpeed = 0;
		break;
	case State_Run:
		m_nCurSpeed = m_nSpeed;
		break;
	case State_Die:
		m_nCurSpeed = 0;
		dieAnimation();
		break;
	case State_Null:
		m_nCurSpeed = 0;
		break;
	}

	m_eOldState = m_eState;
}

void CBaseChar::aniUpdate()
{
	//스테이트가 다를때
	if(m_eOldState != m_eState)
	{
		switch(m_eState)
		{
		case State_Idel:
			m_pNowAni = m_pIdel;
			break;
		case State_Run:
			m_pNowAni = m_pWalk;
			break;
		case State_Die:
			m_pNowAni = m_pDie;
			break;
		}
	}
	//스테이트가 같을때 애니메이션 실행
	else
	{
		auto temp_tex = m_pNowAni->run();
		if(temp_tex == LOOPEND)
		{
			return ;
		}
		else if(temp_tex == LOOPACTIVE)
		{
			return;
		}
		else
		{
			m_pBody->setTex(temp_tex);
		}
	}
}

void CBaseChar::colliderUpdate()
{
	switch(m_eCollider)
	{
	case Coll_Air:

		if(getPos().y > GROUNDPOS)
		{
			m_eCollider = Coll_Ground;
			setPos(ccp(getPos().x,GROUNDPOS));
			m_faddGrivity=0;
			m_vMoveVector.y =0;
		}
		else
		{
			m_faddGrivity += CHARGRAVITY;
		}
		break;
	case Coll_Ground:
		m_faddGrivity = 0;
		m_vMoveVector.y = 0;
		setPos(ccp(getPos().x,GROUNDPOS));
		break;
	case Coll_Box:
		m_faddGrivity = 0;
		m_vMoveVector.y = 0;
		setPos(ccp(getPos().x,BOXPOS));
		break;
	case Coll_Jump:
		m_vMoveVector.y = -JUMPPOWER;
		m_eCollider = Coll_Air;
		break;
	}

	m_vMoveVector.y += m_faddGrivity;
}
//현재 왼쪽을 보고있는게 기본방향.
void CBaseChar::lookUpdate()
{
	switch(m_eLook)
	{
	case Look_Up:
		m_vWeaponVector = ccp(0,1);
		m_vMoveVector.x = 0;
		m_pArm->setRot(90);
		break;
	case Look_RightUp:
		m_vWeaponVector = ccp(1,1);
		m_vMoveVector.x = 1;
		setSiz(ccp(-1,1));
		m_pArm->setRot(45);
		break;
	case Look_Right:
		m_vWeaponVector = ccp(1,0);
		m_vMoveVector.x = 1;
		m_pArm->setRot(0);
		setSiz(ccp(-1,1));
		break;
	case Look_RightDown:
		m_vWeaponVector = ccp(1,-1);
		m_vMoveVector.x = 1;
		m_pArm->setRot(-45);
		setSiz(ccp(-1,1));
		break;
	case Look_Down:
		m_vWeaponVector = ccp(0,-1);
		m_vMoveVector.x = 0;
		m_pArm->setRot(-90);
		break;
	case Look_LeftDown:
		m_vWeaponVector = ccp(-1,-1);
		m_vMoveVector.x = -1;
		m_pArm->setRot(-45);
		setSiz(ccp(1,1));
		break;
	case Look_Left:
		m_vWeaponVector = ccp(-1,0);
		m_vMoveVector.x = -1;
		m_pArm->setRot(0);
		setSiz(ccp(1,1));
		break;
	case Look_LeftUp:
		m_vWeaponVector = ccp(-1,1);
		m_vMoveVector.x = -1;
		setSiz(ccp(1,1));
		m_pArm->setRot(45);
		break;
	}
}

void CBaseChar::weaponUpdate()
{

}

void CBaseChar::moveUpdate()
{
	m_vMoveVector.x *= m_nCurSpeed;
	setPos(ccp(getPos().x + m_vMoveVector.x, (float)(getPos().y + m_vMoveVector.y)));
}

//캐릭터 생성함수
void CBaseChar::makeChar(const char * playerName, int x, int y)
{
	std::string path;
	path.append("Resource/Char/");
	path.append(playerName);
	path.append("/");

	std::string bodypath;
	bodypath = path + "idel_0.png";
	m_pBody = CSprite::create(bodypath.c_str());

	std::string armpath;
	armpath = path;

	switch(m_eNowWeapon)
	{
	case Weapon_Nomal:
		armpath.append("handgun_1.png");
		break;
	case Weapon_Double:
		armpath.append("handgun_2.png");
		break;
	case Weapon_Tripel:
		armpath.append("handgun_3.png");
		break;
	case Weapon_Multiple:
		armpath.append("itemgun_1.png");
		break;
	case Weapon_BigMulti:
		armpath.append("itemgun_2.png");
		break;
	}


	m_pArm = CSprite::create(armpath.c_str());
	m_pBody->setAcp(ccp(0.5,0.5));
	m_pBody->setPos(ccp(0,0));
	addChild(m_pBody);
	m_pArm->setAcp(ccp(0.5,0.5));
	m_pArm->setPos(ccp(x,y));
	//setRect(m_pBody->getRect());
	setAcp(ccp(0.5,0.5));
	setBoundBox(m_pBody->getRect());
	addChild(m_pArm);

	m_pIdel = makeAnimation(path.c_str(),"idel",true,2);
	m_pWalk = makeAnimation(path.c_str(),"run",true,4);
	m_pDie = makeAnimation(path.c_str(),"die",false,1);

	m_pNowAni = m_pIdel;
}

CAnimation * CBaseChar::makeAnimation(const char * charpath, const char * aniname, bool loop, int count)
{
	auto ani = new CAnimation();
	ani->init(150,loop);

	for(int i = 0; i<count; i++)
	{
		char buf[128];
		sprintf_s(buf, "%s%s_%d.png", charpath, aniname, i);
		ani->addFrame(buf);
	}

	return ani;
}

void CBaseChar::Attacked(int Power)
{
	m_nHp -= Power;
	if(m_nHp <= 0)
	{
		m_eState = State_Die;
		switch(m_eCharIndex)
		{
		case Index_Enemy1:
			DataMgr->setScore(100);
			break;
		case Index_Enemy2:
			DataMgr->setScore(200);
			break;
		case Index_Boss1:
			DataMgr->setScore(1000);
			break;
		case Index_Boss2:
			DataMgr->setScore(2000);
			break;
		}
	}
	m_isAttacking = true;
}

void CBaseChar::dieAnimation()
{

	m_nDieAniTime += 16;
	m_fNowAlpha -= 4;

	m_pBody->setCor(ccc4((int)m_fNowAlpha,255,255,255));
	m_pArm->setCor(ccc4((int)m_fNowAlpha,255,255,255));

	if(m_nDieAniTime>1000)
	{
		m_eState = State_Null;
	}
}

void CBaseChar::attackUpdate()
{
	if(m_isAttacking)
	{
		m_nAttackTime += 16;
		if(m_nAttackTime > 200)
		{
			m_nAttackTime = 0;
			m_isAttacking = false;
			m_pBody->setCor(ccc4(255,255,255,255));
			m_pArm->setCor(ccc4(255,255,255,255));
		}
		else
		{
			m_pBody->setCor(ccc4(255,255,0,0));
			m_pArm->setCor(ccc4(255,255,0,0));
		}
	}
}