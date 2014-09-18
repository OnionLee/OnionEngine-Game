#pragma once
#include "Node.h"
class CLable : public CNode
{
public:
	LPD3DXFONT m_pFont;
	std::string m_sText;


	virtual bool init(const char * fontname);
	virtual void render();
	virtual void release();

	void setText(const char * text);

	CLable(void);
	~CLable(void);

	static CLable * create(const char * fontname);
};

