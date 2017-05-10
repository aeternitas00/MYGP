#include "stdafx.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

VOID GraphicsComponent::update(GameObject& rObj)
{
	LPD3DXSPRITE sprite=*RenderManager::GetInstance()->GetSprite();
	//sprite->Draw(~~)
	return VOID();
}


GraphicsComponent::~GraphicsComponent()
{
}
