#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::GameObject(ComponentBase* Components, ...)
{
}

HRESULT GameObject::SetTxt()
{
	return S_OK;
}


VOID GameObject::AddComponent(ComponentBase * Component)
{
	ComponentList.push_back(Component);
}

GameObject::~GameObject()
{
	for (auto it = ComponentList.begin(); it != ComponentList.end();) {
		delete *it; ComponentList.erase(it++);
	}
}

VOID GameObject::update()
{
	for (auto it : ComponentList)
		it->update(*this);
	return;
}
