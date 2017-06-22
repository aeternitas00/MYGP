#pragma once
#include "GameStaticObject.h"
class MoreJumpObj :
	public GameStaticObject
{
	int resettimer;
	int frame;
	bool updown;
public:
	MoreJumpObj();
	~MoreJumpObj();
	virtual RESULT UpdateSub();
	virtual VOID Initialize(char * n);
	virtual VOID SetComponent();
};

