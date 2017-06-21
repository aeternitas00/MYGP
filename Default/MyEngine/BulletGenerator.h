#pragma once
#include "Enemy.h"
class BulletGenerator :
	public GameMovableObject
{
	int type;
public:
	BulletGenerator();
	VOID Initialize(char * n);
	RESULT UpdateSub();
	BulletGenerator(D3DXVECTOR3 & ipos, int id);
	~BulletGenerator();
	virtual VOID SetComponent();
};

