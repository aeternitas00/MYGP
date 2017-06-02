#include "stdafx.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

VOID GraphicsComponent::Update(GameObject* pObj)
{
	if (pObj->txtid == -1) return;
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(pObj->txtid);

	RENDERSQUARE sqr = pObj->GetRenderSquare();
	sqr.x *= temp.spfx; sqr.y *= temp.spfy;
	RECT rtemp = { sqr.x ,sqr.y,sqr.x + temp.spfx,sqr.y + temp.spfy };

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, 0.0,0.0,0.0);
	
	RenderManager::GetInstance()->DrawObj(pObj->pos, pObj->txtid, rtemp, mat);
}


GraphicsComponent::~GraphicsComponent()
{
}
