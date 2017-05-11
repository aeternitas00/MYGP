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
	GraphicsComponent* pGrpComponent;
public:
	GameObject();
	GameObject(D3DXVECTOR3& ipos, int id);
	HRESULT SetTxt(int& id);
	virtual ~GameObject();
	virtual VOID update();
};

