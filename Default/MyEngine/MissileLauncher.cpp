#include "stdafx.h"
#include "MissileLauncher.h"


MissileLauncher::MissileLauncher()
{
}

MissileLauncher::MissileLauncher(D3DXVECTOR3 & ipos)
{
	velocity = D3DXVECTOR3(0,0,0);
	acceleration = D3DXVECTOR3(0, 0, 0);
	pos = ipos;
}


MissileLauncher::~MissileLauncher()
{
}

VOID MissileLauncher::SetComponent()
{
	txtid = TXTID_MISSILE_LBARREL;
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
