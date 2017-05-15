#include "stdafx.h"
#include "GameTerrain.h"


GameTerrain::GameTerrain()
{
}

GameTerrain::GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy,int id) : width(ix),height(iy),GameStaticObject(ipos,id)
{
}

VOID GameTerrain::SetComponent()
{
	TEXTURESET& temp = *RenderManager::GetInstance()->GetTexture(txtid);
	vx = temp.spfx; vy = temp.spfy;
	ComponentList.push_back(new TerrainGraphicsComponent);
}

RESULT GameTerrain::Update()
{
	for (auto it : ComponentList)
		it->Update(this);
	return Default; 
}


GameTerrain::~GameTerrain()
{
}
