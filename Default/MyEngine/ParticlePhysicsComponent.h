#pragma once
#include "PhysicsComponent.h"
class ParticlePhysicsComponent :
	public PhysicsComponent
{
public:
	ParticlePhysicsComponent();
	~ParticlePhysicsComponent();
	virtual VOID Update(GameObject* pObj);
};

