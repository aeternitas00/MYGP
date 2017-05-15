#pragma once
#include "GameStaticObject.h"
class GameTerrain :
	public GameStaticObject
{
protected:
	unsigned int width;
	unsigned int height;
	float vx;
	float vy;
public:
	MYRECT GetTerrainInfo() { return MYRECT{ width,height }; }
	float GetXEnd() { return pos.x + (width*vx); }
	float GetYEnd() { return pos.x + (height*vy); }
	float GetVX() { return vx; }
	float GetVY() { return vy; }
	GameTerrain();
	GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy, int id);
	VOID SetComponent();
	virtual RESULT Update();
	~GameTerrain();
};

