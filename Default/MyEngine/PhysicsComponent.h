#pragma once
#include "stdafx.h"
class PhysicsComponent:public ComponentBase
{
protected:
	RECT volume;
public:
	PhysicsComponent();
	virtual VOID Update(GameObject* pObj);
	virtual ~PhysicsComponent();
};

