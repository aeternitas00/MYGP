#pragma once
#include "GameMovableObject.h"
class EnemyBullet :
	public GameMovableObject
{
public:
	EnemyBullet();
	~EnemyBullet();
	virtual VOID SetComponent();
	virtual RESULT Update();
};

