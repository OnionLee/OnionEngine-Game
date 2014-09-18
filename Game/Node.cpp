#include "StdAfx.h"
#include "Node.h"


CNode::CNode(void)
{
	D3DXMatrixIdentity(&m_LocalMat);
	D3DXMatrixIdentity(&m_WorldMat);

	//메트릭스에 필요한것
	m_Pos = ccp(0,0);
	m_Rot = 0;
	m_Siz = ccp(1,1);
	m_Acp = ccp(0,0);
	//스프라이트에 필요한 것
	m_Cor = ccc4(255,255,255,255);
	m_pTex = NULL;
	m_pParent = NULL;

	m_Rect = ccr(0,0,0,0);
	m_rBoundBox = ccr(0,0,0,0);

	m_isRender = true;
}


CNode::~CNode(void)
{
	release();
}


bool CNode::init()
{

	return true;
}
void CNode::update()
{
	auto itr = m_vChilds.begin();
	FOREACH(m_vChilds,itr)
	{
		(*itr)->update();
	}
}
void CNode::render()
{
	std::sort(m_vChilds.begin(),m_vChilds.end(),Zorder);

	auto itr = m_vChilds.begin();
	FOREACH(m_vChilds,itr)
	{
		if((*itr)->m_isRender)
			(*itr)->render();
	}
}
void CNode::release()
{
	delete m_pTex;
	auto itr = m_vChilds.begin();
	FOREACH(m_vChilds,itr)
	{
		(*itr)->release();
	}

	m_vChilds.clear();
}

void CNode::addChild(CNode * p_Node, int z_oder /*= 0*/)
{
	p_Node->m_pParent = this;
	p_Node->setZorder(z_oder);
	m_vChilds.push_back(p_Node);
}

void CNode::setAcp(D3DXVECTOR2 var)
{
	m_Acp.x = var.x;
	m_Acp.y = var.y;
	setLocalMat();
}

void CNode::setLocalMat()
{
	D3DXVECTOR2 drawAcp = ccp(getRect().right * m_Acp.x,
							getRect().bottom * m_Acp.y);

	D3DXVECTOR2 drawPos = ccp(m_Pos.x - drawAcp.x,
							m_Pos.y - drawAcp.y);

	float DrawRot = m_Rot * 3.141592f / 180.0f;

	D3DXMatrixTransformation2D(&m_LocalMat,
		&drawAcp,
		NULL,
		&m_Siz,
		&drawAcp,
		DrawRot,
		&drawPos);
}
void CNode::setWorldMat()
{
	D3DXMATRIXA16 t;
	D3DXMatrixIdentity(&t);
	for(CNode * p = this; p!=NULL ; p= p->getParent())
	{
		t *= p->m_LocalMat;
	}

	m_WorldMat = t;
}
D3DXMATRIXA16 CNode::getLocalMat()
{
	return m_LocalMat;
}
D3DXMATRIXA16 CNode::getWorldMat()
{
	setWorldMat();
	return m_WorldMat;
}

void CNode::removeChild(CNode * p_Node)
{
	auto itr = m_vChilds.begin();
	FOREACH(m_vChilds,itr)
	{
		if((*itr) == p_Node)
		{
			m_vChilds.erase(itr);
			p_Node->release();
			p_Node = 0;
			break;
		}
	}
}

//앵커 설정후에 호출하면 정확하다.
void CNode::setBoundBox()
{
	float dis_x = (getRect().right * m_Acp.x);
	float dis_y = (getRect().bottom * m_Acp.y);

	m_rBoundBox.left = - dis_x;
	m_rBoundBox.top = - dis_y;
	m_rBoundBox.right = getRect().right - dis_x;
	m_rBoundBox.bottom = getRect().bottom - dis_y;

}

RECT CNode::getBoundBox()
{
	RECT NOWBoundBox;

	NOWBoundBox.left = m_rBoundBox.left + getPos().x;
	NOWBoundBox.top = m_rBoundBox.top + getPos().y;
	NOWBoundBox.right = m_rBoundBox.right + getPos().x;
	NOWBoundBox.bottom = m_rBoundBox.bottom + getPos().y;

	return NOWBoundBox;
}

void CNode::setBoundBox(RECT rect)
{
	float dis_x = (rect.right * m_Acp.x);
	float dis_y = (rect.bottom * m_Acp.y);
	
	m_rBoundBox.left =  - dis_x;
	m_rBoundBox.top =  - dis_y;
	m_rBoundBox.right =  rect.right - dis_x;
	m_rBoundBox.bottom = rect.bottom - dis_y;
}

bool CNode::CircleByCircle(CNode * p_target,int offset)
{
	auto p1 = p_target->getPos();
	auto p2 = getPos();

	float x_len = p1.x - p2.x;
	x_len*=x_len;
	float y_len = p1.y - p2.y;
	y_len*=y_len;

	if(x_len + y_len<offset)
		return true;
	else
		return false;


}

bool CNode::RectByRect(CNode * p_target)
{
	auto b1 = p_target->getBoundBox();
	auto b2 = getBoundBox();


	if(b1.top < b2.bottom &&
		b2.top < b1.bottom &&
		b1.right > b2.left &&
		b2.right > b1.left)
	{
		return true;
	}

	return false;
}



RECT MakeRect(int x, int y, int w, int h)
{
	RECT temp;
	temp.left = x;
	temp.top = y;
	temp.right = w;
	temp.bottom = h;

	return temp;
}

bool Zorder(CNode * a, CNode * b)
{
	return a->m_nZorder > b->m_nZorder;
}


