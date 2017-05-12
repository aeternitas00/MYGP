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
	std::list<ComponentBase*> ComponentList;;
public:
	GameObject();
	GameObject(D3DXVECTOR3& ipos, int id);
	HRESULT SetTxt(int& id);
	~GameObject();
	VOID Update();
	virtual VOID SetComponent();
};

