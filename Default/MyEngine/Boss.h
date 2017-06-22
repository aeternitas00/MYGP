#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
protected:
	int hp;
	int stat;
	int frame;
	bool tlfr;
public:
	virtual RENDERSQUARE GetRenderSquare();
	virtual RESULT UpdateSub();
	virtual VOID SetComponent();
	VOID GetHitted();
	VOID DoDeath();
	VOID SetStat(int i) { stat = i; }
	VOID SetLook(bool i) { tlfr = i; }
	Boss();
	~Boss();
};

