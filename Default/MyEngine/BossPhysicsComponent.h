#pragma once
#include "PhysicsComponent.h"
class BossPhysicsComponent :
	public PhysicsComponent
{
public:
	BossPhysicsComponent();
	~BossPhysicsComponent();
	virtual RESULT Update(GameObject* pObj);
};

