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
	virtual bool IsMoving() { return moving; }
	virtual D3DXVECTOR3 GetVel() { return velocity; }
	virtual bool InRange() {return (frame > 0 && frame < maxframe);	}
};

