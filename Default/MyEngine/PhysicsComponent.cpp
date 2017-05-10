#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}

VOID PhysicsComponent::update(GameObject& rObj)
{
	//resolveCollision();
	return VOID();
}

VOID PhysicsComponent::update(GameMovableObject& rObj)
{
	rObj.velocity += rObj.acceleration;
	rObj.pos += rObj.velocity;
	//resolveCollision();
	return;
}


PhysicsComponent::~PhysicsComponent()
{
}
