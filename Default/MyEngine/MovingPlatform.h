#pragma once
#include "GameMovableObject.h"
class MovingPlatform :
	public Platform
{
	D3DXVECTOR3 velocity;
	FRECT sensor;
	bool moving;
	int type;
	int frame;
	int maxframe;
public:
	MovingPlatform();
	virtual VOID Initialize(char * n);
	~MovingPlatform();
	virtual RESULT UpdateSub();
	virtual VOID SetComponent();
};

