#pragma once
#include "ComponentBase.h"
class BossScript :
	public ComponentBase
{
	clock_t before;
	clock_t after;
	short trigger;
	int frame;
public:
	BossScript();
	virtual RESULT Update(GameObject* pObj);
	~BossScript();
};

