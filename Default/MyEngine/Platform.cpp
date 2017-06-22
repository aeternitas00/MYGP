#include "stdafx.h"
#include "Platform.h"


Platform::Platform()
{
}


Platform::~Platform()
{
}


RESULT Platform::UpdateSub()
{
	return Default;
}

VOID Platform::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
}

VOID Platform::SetComponent()
{
	TEXTURESET& temp = *RenderManager::GetInstance()->GetTexture(txtid);
	vx = float(temp.spfx); vy = float(temp.spfy);
	ComponentList.push_back(new GraphicsComponent);
}
