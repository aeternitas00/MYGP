#include "stdafx.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{

}

PlayerBullet::PlayerBullet(Player* pObj):GameMovableObject(pObj->pos,D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 0),TXTID_PLAYER_BULLET)
{
	short dir = pObj->GetDir();
	pos.x += 16.25f;
	pos.y += 16.0f;
	if (pObj->IsLanded())pos.x += 18.25f*dir; else {
		pos.x += 12.5f * dir; pos.y -= 5.0f;
	}
	velocity.x = 7.0f*(float)dir;
}

VOID PlayerBullet::SetComponent() {
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
RESULT PlayerBullet::UpdateSub()
{
	if (!IsInScreen()) return OutOfScreen; // temporal(delete self
	auto TerrainList = SystemManager::GetInstance()->GetTerrainList();
	for (auto it : TerrainList)
	{
		if (it->IsThroughable()) continue;
		if (it->pos.x - 8 <= pos.x  && it->GetXEnd() + 8 >= pos.x) {
			if (it->pos.y - 7 <= pos.y  && it->GetYEnd() + 7 >= pos.y)
				return Destroy;
		}
	}
	return Default;
}

PlayerBullet::~PlayerBullet()
{
}
