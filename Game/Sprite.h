#pragma once
#include "Node.h"
#include "Texture2D.h"
class CSprite : public CNode
{
public:
	CSprite(void);
	~CSprite(void);

	virtual bool init(const char * filename);
	virtual void render();
	virtual void release();

	static CSprite * create(const char * filename);
};

