#include "stdafx.h"
#include "EnemyBulletPhysicsComponent.h"


EnemyBulletPhysicsComponent::EnemyBulletPhysicsComponent()
{
}


EnemyBulletPhysicsComponent::~EnemyBulletPhysicsComponent()
{
}
RESULT EnemyBulletPhysicsComponent::Update(GameObject * pObj)
{
	EnemyBullet* temp = dynamic_cast<EnemyBullet*>(pObj);
	if (temp == NULL) return Default;
	
	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	FRECT rect = temp->GetVolume();

	if (!temp->IsCT()) {
	auto TerrainList = GET_LIST_OUT(GameTerrain);
		for (auto it : *TerrainList)
		{
			if (it->IsThroughable()) continue;
			if (it->pos.x - 2 <= temp->pos.x  && it->GetXEnd() + 2 >= temp->pos.x) {
				if (it->pos.y - 2 <= temp->pos.y  && it->GetYEnd() + 2 >= temp->pos.y)
				{
					temp->SetStat(Destroy); break;
				}
			}
		}
	}
	return Default;
}
