#pragma once
#include "Box.h"

class CConBox : public CBox
{
public:
	virtual bool init();
	CConBox(void);
	~CConBox(void);

	static CConBox * craete();
};


