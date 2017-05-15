#include "stdafx.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

VOID GraphicsComponent::Update(GameObject* pObj)
{
	if (pObj->txtid == -1) return;
	LPD3DXSPRITE sprite=*RenderManager::GetInstance()->GetSprite();
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(pObj->txtid);
	RECT rtemp = { 0,0,temp.spfx,temp.spfy };
	sprite->Draw(temp.txt, &rtemp,NULL,&pObj->pos,D3DXCOLOR(1,1,1,1.0f));
	return VOID();
}


GraphicsComponent::~GraphicsComponent()
{
}
