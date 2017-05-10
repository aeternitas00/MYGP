#pragma once
#include "stdafx.h"

class ComponentBase;
class GraphicsComponent;
class PhysicsComponent;
class GameObject
{
public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
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

