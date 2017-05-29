#pragma once
#include "ComponentBase.h"
class IntroScript :
	public ComponentBase
{
	clock_t before;
	clock_t after;
	short trigger;
public:
	IntroScript();
	~IntroScript();
	virtual VOID Update(GameObject* pObj);
};

