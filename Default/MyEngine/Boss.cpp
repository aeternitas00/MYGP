#include "stdafx.h"
#include "Boss.h"


RENDERSQUARE Boss::GetRenderSquare()
{
	return RENDERSQUARE{0,0};
}

RESULT Boss::UpdateSub()
{
	return Default;
}

VOID Boss::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

Boss::Boss()
{
}


Boss::~Boss()
{
}
