#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(D3DXVECTOR3 & ipos)
{
}


EnemyBullet::~EnemyBullet()
{
}

VOID EnemyBullet::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
