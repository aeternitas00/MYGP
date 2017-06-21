#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(D3DXVECTOR3 & ipos, int id)
{
	pos = ipos;
	txtid = id;
}


Enemy::~Enemy()
{
}
