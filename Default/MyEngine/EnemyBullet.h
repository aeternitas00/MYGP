#pragma once
#include "GameMovableObject.h"
class EnemyBullet :
	public GameMovableObject
{
public:
	EnemyBullet();
	EnemyBullet(D3DXVECTOR3& ipos);
	~EnemyBullet();
	virtual VOID SetComponent();
};

