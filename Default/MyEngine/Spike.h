#pragma once
#include "Obstacle.h"
class Spike :
	public Obstacle
{
private:

public:
	Spike(); 
	Spike(D3DXVECTOR3 & ipos, int id,short dir);
	~Spike();
	virtual RENDERSQUARE GetRenderSquare();
	virtual VOID SetComponent();
};

