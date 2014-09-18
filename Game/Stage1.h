#pragma once
#include "MainLogic.h"
class Stage1 : public MainLogic
{
public:
	Stage1(void);
	~Stage1(void);

	virtual bool init();
	virtual void update();

	virtual void Flag1();
	virtual void Flag2();
	virtual void Flag3();
	virtual void Flag4();
	virtual void Flag5();


	MAKE_CREATE(Stage1);
};

