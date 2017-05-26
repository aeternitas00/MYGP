#pragma once
#include "PhysicsComponent.h"
class PlayerBulletPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual VOID Update(GameObject* pObj);
	PlayerBulletPhysicsComponent();
	~PlayerBulletPhysicsComponent();
};

