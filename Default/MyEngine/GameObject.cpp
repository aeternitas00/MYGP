#include "stdafx.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

GameObject::GameObject() :pGrpComponent(new GraphicsComponent),pPhsComponent(new PhysicsComponent)
{

}

HRESULT GameObject::SetTxt()
{
	return S_OK;
}



GameObject::~GameObject()
{
	delete pGrpComponent;
	delete pPhsComponent;
}

VOID GameObject::update()
{
	pGrpComponent->update(*this);
	pPhsComponent->update(*this);
	return;
}
