#pragma once
#include "stdafx.h"
class PhysicsComponent:public ComponentBase
{
private:
	RECT volume;
public:
	PhysicsComponent();
	virtual VOID update(GameObject& rObj);
	virtual ~PhysicsComponent();
};

