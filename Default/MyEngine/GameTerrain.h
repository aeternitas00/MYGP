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
	bool canthrough;
public:
	MYRECT GetTerrainInfo() { return MYRECT{ width,height }; }
	float GetXEnd() { return pos.x + (width*vx); }
	float GetYEnd() { return pos.y + (height*vy); }
	float GetVX() { return vx; }
	float GetVY() { return vy; }
	bool IsThroughable() {	return canthrough;}
	GameTerrain();
	GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy, int id,bool ct);
	VOID SetComponent();
	virtual RESULT Update();
	~GameTerrain();
};

