#include "StdAfx.h"
#include "Sprite.h"
#include "Director.h"


CSprite::CSprite(void)
{
}


CSprite::~CSprite(void)
{
}

bool CSprite::init(const char * filename)
{
	if(!CNode::init())
		return false;

	CTexture2D * temp = new CTexture2D();
	temp->LoadFromFile(filename);
	setTex(temp);
	setRect(temp->m_rRect);

	return true;
}
void CSprite::render()
{
	CNode::render();
	DrawMgr->m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	DrawMgr->m_pd3dSprite->SetTransform(&getWorldMat());
	DrawMgr->m_pd3dSprite->Draw(getTex()->m_pTexture,&getRect(),NULL,&D3DXVECTOR3(0,0,0),getCor());
	DrawMgr->m_pd3dSprite->End();
}
void CSprite::release()
{
	CNode::release();
}

CSprite * CSprite::create(const char * filename)
{
	CSprite * temp = new CSprite();
	if(!temp->init(filename))
	{
		delete temp;
		temp = NULL;
		return NULL;
	}
	
	return temp;
}