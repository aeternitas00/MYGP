#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(D3DXVECTOR3 & ipos,int id)
{
	pos = ipos; txtid = id; stat = Default;
}

RESULT EnemyBullet::UpdateSub() {
	if (!IsInScreen()) return OutOfScreen; // temporal(delete self;
	return stat;
}


EnemyBullet::~EnemyBullet()
{
}

VOID EnemyBullet::PushBackVolume(FRECT &rect)
{
	Volume.push_back(rect);
}

VOID EnemyBullet::SetComponent()
{
	ComponentList.push_back(new EnemyBulletPhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
