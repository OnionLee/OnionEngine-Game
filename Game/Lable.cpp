#include "StdAfx.h"
#include "Lable.h"
#include "Director.h"


CLable::CLable(void)
{
	m_pFont = NULL;
}


CLable::~CLable(void)
{

}

CLable * CLable::create(const char * fontname)
{


	CLable * temp = new CLable;
	if(!temp->init(fontname))
	{
		delete temp;
		temp = NULL;
		return NULL;
	}

	return temp;
}

bool CLable::init(const char * fontname)
{
	if(!CNode::init())
		return false;

	D3DXCreateFont(DrawMgr->m_pd3dDevice,
					60,
					30,
					500,
					1,
					false,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					ANTIALIASED_QUALITY,
					1,
					fontname,
					&m_pFont);


	if(m_pFont == NULL)
		return false;
	else
	{	
		this->setCor(ccc4(255,0,0,0));
		return true;
	}
	
}

void CLable::render()
{
	CNode::render();

	DrawMgr->m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	DrawMgr->m_pd3dSprite->SetTransform(&getWorldMat());
	m_pFont->DrawTextA(DrawMgr->m_pd3dSprite,
		m_sText.c_str(),
		-1,
		&getRect(),
		D3DFMT_A8B8G8R8,
		getCor());

	DrawMgr->m_pd3dSprite->End();
}
void CLable::release()
{
	m_pFont->Release();

	CNode::release();
}

void CLable::setText(const char * text)
{
	m_sText = text;
	setRect(ccr(0,0,m_sText.size() * 30, 60));
}
