#include "stdafx.h"
#include "GameStaticObject.h"


GameStaticObject::GameStaticObject():dir(0)
{
}
GameStaticObject::GameStaticObject(D3DXVECTOR3& ipos, int id) : GameObject(ipos,id),dir(0)
{
}
VOID GameStaticObject::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}

GameStaticObject::~GameStaticObject()
{
}
