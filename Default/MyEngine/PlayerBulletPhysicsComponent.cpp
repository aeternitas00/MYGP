#include "stdafx.h"
#include "PlayerBulletPhysicsComponent.h"


VOID PlayerBulletPhysicsComponent::Update(GameObject * pObj)
{
	PlayerBullet* temp = dynamic_cast<PlayerBullet*>(pObj);
	if (temp == NULL) return;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	FRECT rect = temp->GetVolume();
	rect.left += temp->pos.x; rect.right += temp->pos.x;
	rect.top += temp->pos.y; rect.bottom += temp->pos.y;

	auto SavePointList = GET_LIST_OUT(SavePoint);
	for (auto it : *SavePointList)
	{
		FRECT obsvolume = it->GetVolume();
		FRECT obshitbox;
		obshitbox.top = (it->pos.y + obsvolume.top); obshitbox.bottom = (it->pos.y + obsvolume.bottom);
		obshitbox.left = (it->pos.x + obsvolume.left);	obshitbox.right = (it->pos.x + obsvolume.right);
		if (CollisionCheck(obshitbox, rect))
		{
			temp->SetStat(Destroy); it->SetStat(1); 
			GET_SYSMANAGER()->SaveSF();
			return;
		}
	}
	auto TerrainList = GET_LIST_OUT(GameTerrain);
	for (auto it : *TerrainList)
	{
		if (it->IsThroughable()) continue;
		if (it->pos.x - 8 <= temp->pos.x  && it->GetXEnd() + 8 >= temp->pos.x) {
			if (it->pos.y - 7 <= temp->pos.y  && it->GetYEnd() + 7 >= temp->pos.y)
			{
				temp->SetStat(Destroy);  return;
			}
		}
	}
}

PlayerBulletPhysicsComponent::PlayerBulletPhysicsComponent()
{
}


PlayerBulletPhysicsComponent::~PlayerBulletPhysicsComponent()
{
}
