#include "stdafx.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

VOID GraphicsComponent::update(GameObject& rObj)
{
	if (rObj.txtid == -1) return;
	LPD3DXSPRITE sprite=*RenderManager::GetInstance()->GetSprite();
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(rObj.txtid);
	RECT rtemp = { 0,0,temp.spfx,temp.spfy };
	sprite->Draw(temp.txt, &rtemp,NULL,&rObj.pos,D3DXCOLOR(1,1,1,1.0f));
	return VOID();
}


GraphicsComponent::~GraphicsComponent()
{
}
