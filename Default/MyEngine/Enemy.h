#pragma once
#include "GameMovableObject.h"
class Enemy :
	public GameMovableObject
{
public:
	Enemy();
	Enemy(D3DXVECTOR3& ipos, int id);
	~Enemy();
};

