#pragma once
#include "GameMovableObject.h"
class EnemyBullet :
	public GameMovableObject
{
	RESULT stat;
public:
	EnemyBullet();
	EnemyBullet(D3DXVECTOR3& ipos,int id);
	virtual RESULT UpdateSub();
	~EnemyBullet();
	VOID SetStat(RESULT is) { stat = is; }
	
	virtual VOID SetComponent();
};

