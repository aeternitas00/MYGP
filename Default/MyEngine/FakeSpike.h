#pragma once
#include "Spike.h"
class FakeSpike :
	public Spike
{
private:
	D3DXVECTOR3 velocity;
	FRECT sensor;
	bool moving;
public:
	FakeSpike();
	VOID Initialize(char * n);
	~FakeSpike();
	RESULT UpdateSub();
	VOID SetComponent();
};

