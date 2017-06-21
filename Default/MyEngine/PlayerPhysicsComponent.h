#pragma once
#include "PhysicsComponent.h"
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual RESULT Update(GameObject* pObj);
	PlayerPhysicsComponent();
	~PlayerPhysicsComponent();
};

