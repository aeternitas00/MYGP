#pragma once
#include "GameMovableObject.h"
class Particle :
	public GameMovableObject
{
private:
	D3DXCOLOR color;
public:
	Particle();
	Particle(D3DXVECTOR3, D3DXVECTOR3,D3DXCOLOR,int);
	virtual RESULT UpdateSub();
	virtual VOID SetComponent();
	D3DXCOLOR GetColor() { return color; }
	~Particle();
};

