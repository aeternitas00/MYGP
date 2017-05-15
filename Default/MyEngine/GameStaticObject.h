#pragma once
#include "GameObject.h"
class GameStaticObject :
	public GameObject
{
public:
	GameStaticObject();
	GameStaticObject(D3DXVECTOR3& ipos, int id);
	VOID SetComponent();
	~GameStaticObject();
};

