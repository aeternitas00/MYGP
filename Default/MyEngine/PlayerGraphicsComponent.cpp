#include "stdafx.h"
#include "PlayerGraphicsComponent.h"


RESULT PlayerGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return Default;
	Player* ptemp = dynamic_cast<Player*>(pObj);

	if (ptemp == NULL) return Default;
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(ptemp->txtid);

	RENDERSQUARE sqr= ptemp->GetRenderSquare();
	sqr.x *= temp.spfx; sqr.y *= temp.spfy;
	RECT rtemp = { sqr.x ,sqr.y,sqr.x +temp.spfx,sqr.y+temp.spfy };

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, &D3DXVECTOR2(temp.spfx / 2, temp.spfy / 2), pObj->angle, NULL);

	RenderManager::GetInstance()->DrawObj(pObj->pos, pObj->txtid, rtemp, mat);
	}

PlayerGraphicsComponent::PlayerGraphicsComponent()
{
}


PlayerGraphicsComponent::~PlayerGraphicsComponent()
{
}
