#pragma once
#include "stdafx.h"
#include <list>
using namespace std;
class ComponentBase;
class GraphicsComponent;
class PhysicsComponent;
class GameObject
{
public:
	D3DXVECTOR3 pos;
	int txtid;
protected:
	std::list<ComponentBase*> ComponentList;
	std::list<FRECT> Volume;
public:
	GameObject();
	GameObject(D3DXVECTOR3& ipos, int id);
	VOID SetTxt(const int id);
	~GameObject();

	bool IsInScreen() { return pos.x<MAX_X&&pos.x>-100 && pos.y<MAX_Y&&pos.y>-100 ? true : false; }
	RESULT Update();
	virtual RENDERSQUARE GetRenderSquare();
	virtual RESULT UpdateSub();
	virtual short GetDir() { return 0; }
	std::list<FRECT> GetVolume() { return Volume; }
	VOID UpdateByMovingScene(int side);
	virtual VOID SetComponent();
};

