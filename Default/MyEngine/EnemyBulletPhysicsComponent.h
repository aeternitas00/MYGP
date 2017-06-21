#pragma once
#include "PhysicsComponent.h"
class EnemyBulletPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual RESULT Update(GameObject* pObj);
	EnemyBulletPhysicsComponent();
	~EnemyBulletPhysicsComponent();
};

