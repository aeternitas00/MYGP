#pragma once
#include "Enemy.h"
class BulletGenerator :
	public Enemy
{
public:
	BulletGenerator();
	BulletGenerator(D3DXVECTOR3& ipos);
	~BulletGenerator();
	virtual VOID SetComponent();
};

