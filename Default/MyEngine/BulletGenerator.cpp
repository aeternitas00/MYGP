#include "stdafx.h"
#include "BulletGenerator.h"


BulletGenerator::BulletGenerator()
{
}

VOID BulletGenerator::Initialize(char* n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	int delay = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
	EnemyBullet sample(pos, TXTID_DBOSHY_BULLET,true);

	MyPolygon temppol;
	temppol.push_back(D3DXVECTOR2(0, 0));
	temppol.push_back(D3DXVECTOR2(18, 0));
	temppol.push_back(D3DXVECTOR2(18,16));
	temppol.push_back(D3DXVECTOR2(0, 16));
	sample.PushBackSATVolume(temppol);

	BulletGenerate1* input = new BulletGenerate1(-1, delay, D3DXVECTOR3(-8, 0, 0), pos, sample);
	AddComponent(input);
}

RESULT BulletGenerator::UpdateSub()
{
	return Default;
}

BulletGenerator::BulletGenerator(D3DXVECTOR3 & ipos, int id)
{
	txtid = id;
	velocity = D3DXVECTOR3(0,0,0);
	acceleration = D3DXVECTOR3(0, 0, 0);
	pos = ipos;
}


BulletGenerator::~BulletGenerator()
{
}

VOID BulletGenerator::SetComponent()
{
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
