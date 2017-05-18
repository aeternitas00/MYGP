#pragma once
#include "Enemy.h"
class MissileLauncher :
	public Enemy
{
public:
	MissileLauncher();
	MissileLauncher(D3DXVECTOR3& ipos);
	~MissileLauncher();
	virtual VOID SetComponent();
};

