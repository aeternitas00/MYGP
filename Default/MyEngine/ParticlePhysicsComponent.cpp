#include "stdafx.h"
#include "ParticlePhysicsComponent.h"


ParticlePhysicsComponent::ParticlePhysicsComponent()
{
}


ParticlePhysicsComponent::~ParticlePhysicsComponent()
{
}

VOID ParticlePhysicsComponent::Update(GameObject * pObj)
{
	Particle* temp = dynamic_cast<Particle*>(pObj);
	if (temp == NULL) return;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	auto TerrainList = GET_LIST_OUT(GameTerrain);

	for (auto it : *TerrainList)
	{
		if (it->IsThroughable()) continue;
		if (it->pos.x - 2.5 <= temp->pos.x  && it->GetXEnd() + 2.5 >= temp->pos.x) {
			if (it->pos.y - 2.5 <= temp->pos.y  && it->GetYEnd() + 2.5 >= temp->pos.y)
			{
				temp->velocity.x = 0; temp->velocity.y = 0;
				temp->acceleration.x = 0; temp->acceleration.y = 0;
			}
		}
	}
}
