#pragma once
#include "PhysicsComponent.h"
class EnemyBulletPhysicsComponent :
	public PhysicsComponent
{
public:
	virtual VOID Update(GameObject* pObj);
	EnemyBulletPhysicsComponent();
	~EnemyBulletPhysicsComponent();
};

