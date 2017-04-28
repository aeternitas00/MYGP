#pragma once
#include "stdafx.h"
#include <list>
using namespace std;
class ComponentBase;
class GameObject
{
public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
protected:
	LPDIRECT3DTEXTURE9 txt;
	std::list<ComponentBase*> ComponentList;
	VOID AddComponent(ComponentBase* Component);
public:
	GameObject();
	GameObject(ComponentBase* Component, ...);
	HRESULT SetTxt();
	virtual ~GameObject();
	VOID update();
};

