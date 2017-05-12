#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}

VOID PhysicsComponent::Update(GameObject& rObj)
{
	//resolveCollision();
	return VOID();
}

VOID PhysicsComponent::Update(GameMovableObject& rObj)
{
	rObj.velocity += rObj.acceleration;
	rObj.pos += rObj.velocity;
	//resolveCollision();
	return;
}


PhysicsComponent::~PhysicsComponent()
{
}
