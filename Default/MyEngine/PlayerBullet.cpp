#include "stdafx.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{

}

PlayerBullet::PlayerBullet(Player* pObj):GameMovableObject(pObj->pos,D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 0),TXTID_PLAYER_BULLET)
{
	short dir = pObj->GetDir();
	pos.x += 36.5f;
	pos.y += 32;
	if (pObj->IsLanded())pos.x += 36.5f*dir; else {
		pos.x += 25 * dir; pos.y -= 10;
	}
	velocity.x = 7.0f*(float)dir;
}

VOID PlayerBullet::SetComponent() {
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
RESULT PlayerBullet::Update()
{
	if (!IsInScreen()) return Destroy; // temporal(delete self
	auto TerrainList = SystemManager::GetInstance()->GetTerrainList();
	for (auto it : TerrainList)
	{
		if (it->pos.x -8<= pos.x  && it->GetXEnd()+8 >= pos.x  ) {
			if (it->pos.y -7<= pos.y  && it->GetYEnd() +7<= pos.y )return Destroy;
		}
	}
	for (auto it : ComponentList)
		it->Update(this);
	return Default;
}
PlayerBullet::~PlayerBullet()
{
}
