#include "stdafx.h"
#include "GameStaticObject.h"


GameStaticObject::GameStaticObject():dir(0)
{
}
GameStaticObject::GameStaticObject(D3DXVECTOR3& ipos, int id) : GameObject(ipos,id),dir(0)
{
}

VOID GameStaticObject::Initialize(char* n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
	if (strlen(temp) != 0)
	{
		dir = atoi(strtok_s(NULL, " ", &temp));
	}
}

VOID GameStaticObject::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}

GameStaticObject::~GameStaticObject()
{

}

RENDERSQUARE GameStaticObject::GetRenderSquare()
{
	return RENDERSQUARE{ dir,0 };
}
