#include "stdafx.h"
#include "TerrainGraphicsComponent.h"


TerrainGraphicsComponent::TerrainGraphicsComponent()
{
}


TerrainGraphicsComponent::~TerrainGraphicsComponent()
{
}

VOID TerrainGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return;
	LPD3DXSPRITE sprite = *RenderManager::GetInstance()->GetSprite();
	GameTerrain* Ttemp = dynamic_cast<GameTerrain*>(pObj);
	RECT rtemp = { 0,0,Ttemp->GetVX(),Ttemp->GetVY() };
	MYRECT rect = Ttemp->GetTerrainInfo();
	auto Ptemp = pObj->pos;
	for (auto x = 0; x < rect.x; x++) {
		Ptemp.x = pObj->pos.x+ Ttemp->GetVX()*x;
		for (auto y = 0; y < rect.y; y++) {
			Ptemp.y = pObj->pos.y+ Ttemp->GetVY()*y;
			sprite->Draw(RenderManager::GetInstance()->GetTexture(pObj->txtid)->txt, &rtemp, NULL, &Ptemp, D3DXCOLOR(1, 1, 1, 1.0f));
		}
	}
	

	return VOID();
}
