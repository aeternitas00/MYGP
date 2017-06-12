#include "stdafx.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet():stat(Default)
{

}

PlayerBullet::PlayerBullet(Player* pObj):GameMovableObject(pObj->pos,D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 0),TXTID_PLAYER_BULLET), stat(Default)
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
	Volume=FRECT{ 0,8,0,7 };

	ComponentList.push_back(new PlayerBulletPhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
RESULT PlayerBullet::UpdateSub()
{
	if (!IsInScreen()) return OutOfScreen; // temporal(delete self;
	return stat;
}

PlayerBullet::~PlayerBullet()
{
}
