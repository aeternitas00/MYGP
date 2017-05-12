#pragma once
#include "stdafx.h"
class PhysicsComponent:public ComponentBase
{
private:
	RECT volume;
public:
	PhysicsComponent();
	virtual VOID Update(GameObject& rObj);
	virtual VOID Update(GameMovableObject & rObj);
	virtual ~PhysicsComponent();
};

