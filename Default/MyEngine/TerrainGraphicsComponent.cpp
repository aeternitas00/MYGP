#include "stdafx.h"
#include "TerrainGraphicsComponent.h"


TerrainGraphicsComponent::TerrainGraphicsComponent()
{
}


TerrainGraphicsComponent::~TerrainGraphicsComponent()
{
}

RESULT TerrainGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return Default;

	GameTerrain* Ttemp = dynamic_cast<GameTerrain*>(pObj);

	LPD3DXSPRITE sprite;
	D3DXCreateSprite(*RenderManager::GetInstance()->GetDevice(), &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	int vx = Ttemp->GetVX();
	int vy = Ttemp->GetVY();
	auto RSQR = Ttemp->GetRenderSquare();

	RECT rtemp = { 0+(vx*RSQR.x),0 + (vy*RSQR.y),vx+(vx*RSQR.x),vy+ (vy*RSQR.y) };
	MYRECT rect = Ttemp->GetTerrainInfo();
	
	D3DXVECTOR3 ct2(0, 0, 0);

	D3DXMatrixTranslation(&mat, pObj->pos.x, pObj->pos.y, 0.0);
	D3DXMatrixMultiply(&mat, &mat, RenderManager::GetInstance()->GetWorldMatrix());
	sprite->SetTransform(&mat);

	for (unsigned int x = 0; x < rect.x; x++) {
		ct2.x = vx*x;
		for (unsigned int y = 0; y < rect.y; y++) {
			ct2.y = vy*y;
			sprite->Draw(RenderManager::GetInstance()->GetTexture(pObj->txtid)->txt, &rtemp, NULL, &ct2, D3DXCOLOR(1, 1, 1, 1.0f));
		}
	}
	sprite->End();
	sprite->Release();
	return Default;
}
