#include "stdafx.h"
#include "GameStaticObject.h"


GameStaticObject::GameStaticObject()
{
}
GameStaticObject::GameStaticObject(D3DXVECTOR3& ipos, int id) : GameObject(ipos,id)
{
}
VOID GameStaticObject::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}

GameStaticObject::~GameStaticObject()
{
}
