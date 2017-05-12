#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject():pos(D3DXVECTOR3(0,0,0)),txtid(-1)
{
}
GameObject::GameObject(D3DXVECTOR3& ipos,int id): pos(ipos), txtid(id)
{
}

VOID GameObject::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

HRESULT GameObject::SetTxt(int& id)
{
	return S_OK;
}

GameObject::~GameObject()
{
	for (auto it = ComponentList.begin(); it != ComponentList.end();) {
		delete *it; ComponentList.erase(it++);
	}
}

VOID GameObject::Update()
{
	for (auto it : ComponentList)
		it->Update(*this);
}
