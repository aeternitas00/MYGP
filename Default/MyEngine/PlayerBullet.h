#pragma once
#include "GameMovableObject.h"
class PlayerBullet :
	public GameMovableObject
{
public:
	PlayerBullet();
	PlayerBullet(Player* pObj);
	virtual VOID SetComponent();
	virtual RESULT UpdateSub();
	~PlayerBullet();
};

