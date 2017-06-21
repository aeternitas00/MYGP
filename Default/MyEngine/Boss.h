#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
protected:
	int hp;
public:
	virtual RENDERSQUARE GetRenderSquare();
	virtual RESULT UpdateSub();
	virtual VOID SetComponent();
	Boss();
	~Boss();
};

