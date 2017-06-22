#pragma once
#include "GameObject.h"
class GameStaticObject :
	public GameObject
{
protected:
	short dir;
public:
	GameStaticObject();
	GameStaticObject(D3DXVECTOR3& ipos, int id);
	virtual VOID Initialize(char * n);
	virtual short GetDir() { return dir; }
	virtual VOID SetComponent();
	~GameStaticObject();
	virtual RENDERSQUARE GetRenderSquare();
};

