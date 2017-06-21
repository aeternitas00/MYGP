#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(D3DXVECTOR3 & ipos, int id, bool ict): ct(ict)
{
	pos = ipos; txtid = id; stat = Default; angle = 0;
}

RESULT EnemyBullet::UpdateSub() {
	if (!IsInScreen()) return Destroy; // temporal(delete self;
	return stat;
}


EnemyBullet::~EnemyBullet()
{
}



VOID EnemyBullet::SetComponent()
{
	ComponentList.push_back(new EnemyBulletPhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
