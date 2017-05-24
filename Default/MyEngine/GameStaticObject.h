#pragma once
#include "GameObject.h"
class GameStaticObject :
	public GameObject
{
protected:
	short dir;
public:
	GameStaticObject();
	GameStaticObject(D3DXVECTOR3& ipos, int id);
	virtual short GetDir() { return dir; }

	VOID SetComponent();
	~GameStaticObject();
};

