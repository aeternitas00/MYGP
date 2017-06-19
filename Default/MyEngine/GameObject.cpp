#include "stdafx.h"
#include "GameObject.h"

VOID GameObject::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

GameObject::GameObject() :pos(D3DXVECTOR3(0, 0, 0)), txtid(-1), linfo(Loopinfo { false,0,0,0,0 })
{
}

GameObject::GameObject(D3DXVECTOR3& ipos,int id): pos(ipos), txtid(id),angle(0), linfo(Loopinfo{ false,0,0,0,0 })
{
}

VOID GameObject::SetTxt(const int id)
{
	txtid = id;
}

GameObject::~GameObject()
{
	for (auto it = ComponentList.begin(); it != ComponentList.end();) {
		delete *it; ComponentList.erase(it++);
	}
}

VOID GameObject::Initialize(char* n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
	if (strlen(temp) != 0)
	{
		bool animated = atoi(strtok_s(NULL, " ", &temp));
		if (animated)
		{
			int mf = atoi(strtok_s(NULL, " ", &temp));
			int mc = atoi(strtok_s(NULL, " ", &temp));
			SetLoopAnimation(mf - 1, mc - 1);
		}
	}
}

RESULT GameObject::Update()
{
	for (auto it : ComponentList)
	{
		it->Update(this);
	}
	return UpdateSub();
}

RENDERSQUARE GameObject::GetRenderSquare()
{
	if (linfo.ok) {
		linfo.counter++;
		if (linfo.counter > linfo.maxcounter)
		{
			linfo.counter = 0; linfo.frame++;
			if(linfo.frame>linfo.maxframe)
				linfo.frame = 0;
		}
		return RENDERSQUARE{ linfo.frame,0 };
	}
	return RENDERSQUARE{ 0,0 };
}

RESULT GameObject::UpdateSub()
{
	return Default;
}

VOID GameObject::UpdateByMovingScene(int side)
{
	switch (side) {
	case CToLeft:
		pos.x += MAX_X;
		break;
	case CToRight:
		pos.x -= MAX_X;
		break;
	case CToUp:
		pos.y += MAX_Y;
		break;
	case CToDown:
		pos.y -= MAX_Y;
		break;
	}
}
