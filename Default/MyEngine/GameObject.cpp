#include "stdafx.h"
#include "GameObject.h"

VOID GameObject::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

GameObject::GameObject():pos(D3DXVECTOR3(0,0,0)),txtid(-1)
{
}

GameObject::GameObject(D3DXVECTOR3& ipos,int id): pos(ipos), txtid(id),angle(0)
{
}

VOID GameObject::SetTxt(const int id)
{
	txtid = id;
}

GameObject::~GameObject()
{
	for (auto it = ComponentList.begin(); it != ComponentList.end();) {
		delete *it; ComponentList.erase(it++);
	}
}

RESULT GameObject::Update()
{
	for (auto it : ComponentList)
	{
		it->Update(this);
	}
	return UpdateSub();
}

RENDERSQUARE GameObject::GetRenderSquare()
{
	return RENDERSQUARE{ 0,0 };
}

RESULT GameObject::UpdateSub()
{
	return Default;
}

VOID GameObject::UpdateByMovingScene(int side)
{
	switch (side) {
	case CToLeft:
		pos.x += MAX_X;
		break;
	case CToRight:
		pos.x -= MAX_X;
		break;
	case CToUp:
		pos.y += MAX_Y;
		break;
	case CToDown:
		pos.y -= MAX_Y;
		break;
	}
}
