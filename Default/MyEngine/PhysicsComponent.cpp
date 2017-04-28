#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}

VOID PhysicsComponent::update(GameObject& rObj)
{
	rObj.velocity+=rObj.acceleration;
	rObj.pos+=rObj.velocity;
	//resolveCollision();
	return VOID();
}


PhysicsComponent::~PhysicsComponent()
{
}
