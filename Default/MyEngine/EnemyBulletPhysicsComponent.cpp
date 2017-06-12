#include "stdafx.h"
#include "EnemyBulletPhysicsComponent.h"


EnemyBulletPhysicsComponent::EnemyBulletPhysicsComponent()
{
}


EnemyBulletPhysicsComponent::~EnemyBulletPhysicsComponent()
{
}
VOID EnemyBulletPhysicsComponent::Update(GameObject * pObj)
{
	EnemyBullet* temp = dynamic_cast<EnemyBullet*>(pObj);
	if (temp == NULL) return;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	FRECT rect = temp->GetVolume();

	auto TerrainList = SystemManager::GetInstance()->GetTerrainList();
	for (auto it : TerrainList)
	{
		if (it->IsThroughable()) continue;
		if (it->pos.x - 2 <= temp->pos.x  && it->GetXEnd() + 2 >= temp->pos.x) {
			if (it->pos.y - 2 <= temp->pos.y  && it->GetYEnd() + 2 >= temp->pos.y)
			{
				temp->SetStat(Destroy); return;
			}
		}
	}
}
