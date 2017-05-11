#include "stdafx.h"
#include "GameMovableObject.h"


GameMovableObject::GameMovableObject():GameObject(),velocity(D3DXVECTOR3(0,0,0)),acceleration(D3DXVECTOR3(0,0,0)),
pPhsComponent(new PhysicsComponent())
{
}

GameMovableObject::GameMovableObject(D3DXVECTOR3 & ipos, D3DXVECTOR3 & ivel, D3DXVECTOR3 & iacc, int id):
	GameObject(ipos,id),velocity(ivel),acceleration(iacc), pPhsComponent(new PhysicsComponent())
{

}


GameMovableObject::~GameMovableObject()
{
}

VOID GameMovableObject::update()
{
	GameObject::update();
	pPhsComponent->update(*this);
}
