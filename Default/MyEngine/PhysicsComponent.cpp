#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}

VOID PhysicsComponent::Update(GameObject* pObj)
{
	GameMovableObject* temp = dynamic_cast<GameMovableObject*>(pObj);
	if (temp == NULL) return;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;
	//if (temp->pos.y >= 300) { temp->pos.y = 300; temp->velocity.y = 0; } // юс╫ц

	//resolveCollision();
	return;
}

PhysicsComponent::~PhysicsComponent()
{
}
