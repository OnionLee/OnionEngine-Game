#include "StdAfx.h"
#include "Texture2D.h"
#include "Director.h"

CTexture2D::CTexture2D(void)
{
	m_pTexture = 0;
	m_rRect.bottom = 0;
	m_rRect.left = 0;
	m_rRect.right = 0;
	m_rRect.top = 0;
}


CTexture2D::~CTexture2D(void)
{

}


void CTexture2D::LoadFromFile(const char * filename)
{
	auto temp = TexMgr->LoadTexture(filename);

	m_pTexture = temp->m_pTexture;
	m_rRect = temp->m_rRect;
}
