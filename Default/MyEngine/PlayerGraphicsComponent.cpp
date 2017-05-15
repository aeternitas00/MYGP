#include "stdafx.h"
#include "PlayerGraphicsComponent.h"


VOID PlayerGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return;
	Player* ptemp = dynamic_cast<Player*>(pObj);
	if (ptemp == NULL) return;

	LPD3DXSPRITE sprite = *RenderManager::GetInstance()->GetSprite();
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(ptemp->txtid);
	RENDERSQUARE sqr= ptemp->GetRenderSquare();
	sqr.x *= temp.spfx; sqr.y *= temp.spfy;
	RECT rtemp = { sqr.x ,sqr.y,sqr.x +temp.spfx,sqr.y+temp.spfy };
	sprite->Draw(temp.txt, &rtemp, NULL, &pObj->pos, D3DXCOLOR(1, 1, 1, 1.0f));
	return VOID();
}

PlayerGraphicsComponent::PlayerGraphicsComponent()
{
}


PlayerGraphicsComponent::~PlayerGraphicsComponent()
{
}
