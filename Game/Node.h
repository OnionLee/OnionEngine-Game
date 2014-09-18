#pragma once
#include "Texture2D.h"
#define ccp(x,y) D3DXVECTOR2(x,y)
#define ccc4(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define ccr(x,y,w,h) MakeRect(x,y,w,h)

#define MAKE_CREATE(TYPE) static TYPE * create() \
	{ \
	TYPE * temp = new TYPE(); \
	if(!temp->init()) \
	{ \
	 delete temp; \
	 temp = NULL; \
	 return NULL; \
	} \
	return temp; \
	}


#define FOREACH(vector,itr)  \
						for(itr; itr != vector.end(); itr++) \
											


class CNode
{
public:
	CNode(void);
	~CNode(void);

	D3DXMATRIXA16 m_LocalMat;
	D3DXMATRIXA16 m_WorldMat;

	//메트릭스에 필요한것
	D3DXVECTOR2 m_Pos;
	float m_Rot;
	D3DXVECTOR2 m_Siz;
	D3DXVECTOR2 m_Acp;
	RECT m_Rect;
	//스프라이트에 필요한 것
	D3DCOLOR m_Cor;
	CTexture2D * m_pTex;

	//트리관련
	CNode * m_pParent;
	std::vector<CNode *> m_vChilds;

	int m_nZorder;
	

	//충돌관련
	RECT m_rBoundBox;
	void setBoundBox();
	void setBoundBox(RECT rect);
	RECT getBoundBox();

	bool RectByRect(CNode * p_target);

	bool CircleByCircle(CNode * p_target,int offset);

	//함수
	virtual bool init();
	virtual void update();
	virtual void render();
	virtual void release();

	void setLocalMat();
	void setWorldMat();
	void setPos(D3DXVECTOR2 var){m_Pos = var; setLocalMat();}
	void setRot(float var){m_Rot = var; setLocalMat();}
	void setSiz(D3DXVECTOR2 var){m_Siz = var;setLocalMat();}
	void setAcp(D3DXVECTOR2 var);
	void setCor(D3DCOLOR var){m_Cor = var;}
	void setTex(CTexture2D * var){m_pTex = var; setRect(var->m_rRect);}
	void setRect(RECT var){m_Rect = var;}

	D3DXMATRIXA16 getLocalMat();
	D3DXMATRIXA16 getWorldMat();
	D3DXVECTOR2 getPos(){return m_Pos;}
	float getRot(){return m_Rot;}
	D3DXVECTOR2 getSiz(){return m_Siz;}
	D3DXVECTOR2 getAcp(){return m_Acp;}
	D3DCOLOR getCor(){return m_Cor;}
	CTexture2D * getTex(){return m_pTex;}
	RECT getRect(){return m_Rect;}

	CNode * getParent(){return m_pParent;}
	void addChild(CNode * p_Node, int z_oder = 0);
	void removeChild(CNode * p_Node);

	void setZorder(int var){m_nZorder = var;}
	int getZorder(){return m_nZorder;}

	bool m_isRender;


};

RECT MakeRect(int x, int y, int w, int h);

bool Zorder(CNode * a, CNode * b);


