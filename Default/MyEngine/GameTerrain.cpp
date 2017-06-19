#include "stdafx.h"
#include "GameTerrain.h"


RENDERSQUARE GameTerrain::GetRenderSquare()
{
	return RENDERSQUARE{ dir,0 };
}

VOID GameTerrain::Initialize(char * n)
{
	char* temp = NULL;
	txtid = atoi(strtok_s(n, " ", &temp));
	pos.x = atoi(strtok_s(NULL, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	width = atoi(strtok_s(NULL, " ", &temp));
	height = atoi(strtok_s(NULL, " ", &temp));
	canthrough= atoi(strtok_s(NULL, " ", &temp));
	dir = 0;
	if (strlen(temp) != 0)
		dir = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
}

GameTerrain::GameTerrain()
{
}

GameTerrain::GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy,int id,bool ct) : width(ix),height(iy),GameStaticObject(ipos,id),canthrough(ct)
{
	dir = 0;
}

GameTerrain::GameTerrain(D3DXVECTOR3& ipos, unsigned int ix, unsigned int iy, int id, bool ct,int irpos) : width(ix), height(iy), GameStaticObject(ipos, id), canthrough(ct)
{
	dir = irpos;
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
