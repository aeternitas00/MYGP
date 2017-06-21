#pragma once
#include "GameMovableObject.h"
class EnemyBullet :
	public GameMovableObject
{
	RESULT stat;
	bool ct;
public:
	EnemyBullet();
	EnemyBullet(D3DXVECTOR3 & ipos, int id, bool ict);
	virtual RESULT UpdateSub();
	~EnemyBullet();
	VOID SetStat(RESULT is) { stat = is; }
	bool IsCT() { return ct; }
	virtual VOID SetComponent();
};