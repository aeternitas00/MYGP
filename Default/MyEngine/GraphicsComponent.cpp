#include "stdafx.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

VOID GraphicsComponent::Update(GameObject* pObj)
{
	if (pObj->txtid == -1) return;
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(pObj->txtid);
	RECT rtemp = { 0,0,temp.spfx,temp.spfy };
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, pObj->pos.x, pObj->pos.y, 0.0);

	RenderManager::GetInstance()->DrawObj(pObj->pos, pObj->txtid, rtemp, mat);
}


GraphicsComponent::~GraphicsComponent()
{
}
