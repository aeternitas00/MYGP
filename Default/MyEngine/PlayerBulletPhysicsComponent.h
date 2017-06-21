#pragma once
#include "PhysicsComponent.h"
class PlayerBulletPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual RESULT Update(GameObject* pObj);
	PlayerBulletPhysicsComponent();
	~PlayerBulletPhysicsComponent();
};

