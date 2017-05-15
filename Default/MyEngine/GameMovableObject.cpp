#include "stdafx.h"
#include "GameMovableObject.h"


VOID GameMovableObject::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

RESULT GameMovableObject::Update()
{
	for (auto it : ComponentList)
		it->Update(this);
	return Default;
}

GameMovableObject::GameMovableObject():GameObject(),velocity(D3DXVECTOR3(0,0,0)),acceleration(D3DXVECTOR3(0,0,0))
{
}

GameMovableObject::GameMovableObject(D3DXVECTOR3 & ipos, D3DXVECTOR3 & ivel, D3DXVECTOR3 & iacc, int id):
	GameObject(ipos,id),velocity(ivel),acceleration(iacc)
{
}


GameMovableObject::~GameMovableObject()
{
}

