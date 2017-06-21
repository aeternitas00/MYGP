#pragma once
#include "PhysicsComponent.h"
class ParticlePhysicsComponent :
	public PhysicsComponent
{
public:
	ParticlePhysicsComponent();
	~ParticlePhysicsComponent();
	virtual RESULT Update(GameObject* pObj);
};

