#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject():pos(D3DXVECTOR3(0,0,0)),txtid(-1), 
pGrpComponent(new GraphicsComponent())
{

}
GameObject::GameObject(D3DXVECTOR3& ipos,int id): pos(ipos), txtid(id),
	pGrpComponent(new GraphicsComponent())
{
}

HRESULT GameObject::SetTxt(int& id)
{
	return S_OK;
}

//
//VOID GameObject::AddComponent(ComponentBase * Component)
//{
//	ComponentList.push_back(Component);
//}

GameObject::~GameObject()
{
	//for (auto it = ComponentList.begin(); it != ComponentList.end();) {
	//	delete *it; ComponentList.erase(it++);
	//}
}

VOID GameObject::update()
{
	pGrpComponent->update(*this);
	return;
}
