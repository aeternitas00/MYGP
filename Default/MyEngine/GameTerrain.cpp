#include "stdafx.h"
#include "GameTerrain.h"


GameTerrain::GameTerrain()
{
}

GameTerrain::GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy,int id,bool ct) : width(ix),height(iy),GameStaticObject(ipos,id),canthrough(ct)
{
}

VOID GameTerrain::SetComponent()
{
	TEXTURESET& temp = *RenderManager::GetInstance()->GetTexture(txtid);
	vx = float(temp.spfx); vy = float(temp.spfy);
	ComponentList.push_back(new TerrainGraphicsComponent);
}

GameTerrain::~GameTerrain()
{
}
