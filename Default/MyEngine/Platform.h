#pragma once
#include "GameObject.h"
class Platform :
	public GameObject
{
protected:
	float vx;
	float vy;
public:
	Platform();
	~Platform();
	float GetXEnd() { return pos.x + vx; }
	float GetYEnd() { return pos.y + vy; }
	virtual RESULT UpdateSub();
	virtual VOID Initialize(char * n);
	virtual VOID SetComponent();
	virtual bool IsMoving() { return false; }
	virtual D3DXVECTOR3 GetVel() { return D3DXVECTOR3(0, 0, 0); }
	virtual bool InRange() {return true;}
};

