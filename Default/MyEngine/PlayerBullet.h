#pragma once
#include "GameMovableObject.h"
class PlayerBullet :
	public GameMovableObject
{
private:
	RESULT stat;
public:
	PlayerBullet();
	PlayerBullet(Player* pObj);
	virtual VOID SetComponent();
	virtual RESULT UpdateSub();
	VOID SetStat(RESULT is) { stat = is; }
	~PlayerBullet();
};

