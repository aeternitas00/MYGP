#pragma once
#include "GameObject.h"
class GameMovableObject :
	public GameObject
{
public:
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
public:
	GameMovableObject();
	virtual ~GameMovableObject();
};

