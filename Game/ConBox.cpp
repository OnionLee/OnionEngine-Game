#include "StdAfx.h"
#include "ConBox.h"


CConBox::CConBox(void)
{
}


CConBox::~CConBox(void)
{
}


bool CConBox::init()
{
	CBox::init();
	if(rand()%2 == 0)
		CSprite::init("Resource/Box/cont1.png");
	else
		CSprite::init("Resource/Box/cont2.png");

	m_index = Box_ConBox;

	m_nHp = 99999;

	setAcp(ccp(0.5,0.5));
	setBoundBox();
	return true;
}

CConBox * CConBox::craete()
{
	auto t = new CConBox();
	t->init();
	
	return t;
}