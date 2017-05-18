#include "stdafx.h"
#include "PlayerGraphicsComponent.h"


VOID PlayerGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return;
	Player* ptemp = dynamic_cast<Player*>(pObj);
	if (ptemp == NULL) return;

	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(ptemp->txtid);
	RENDERSQUARE sqr= ptemp->GetRenderSquare();
	sqr.x *= temp.spfx; sqr.y *= temp.spfy;
	RECT rtemp = { sqr.x ,sqr.y,sqr.x +temp.spfx,sqr.y+temp.spfy };

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat,ptemp->pos.x, ptemp->pos.y, 0.0);

	RenderManager::GetInstance()->DrawObj(pObj->pos, pObj->txtid, rtemp, mat);
}

PlayerGraphicsComponent::PlayerGraphicsComponent()
{
}


PlayerGraphicsComponent::~PlayerGraphicsComponent()
{
}
