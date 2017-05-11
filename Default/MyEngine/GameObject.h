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

protected:
	LPDIRECT3DTEXTURE9 txt;	
	GraphicsComponent* pGrpComponent;
	PhysicsComponent* pPhsComponent;
public:
	GameObject();
	HRESULT SetTxt();
	virtual ~GameObject();
	VOID update();
};

