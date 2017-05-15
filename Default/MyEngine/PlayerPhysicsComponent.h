#pragma once
#include "PhysicsComponent.h"
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual VOID Update(GameObject* pObj);
	PlayerPhysicsComponent();
	~PlayerPhysicsComponent();
};

