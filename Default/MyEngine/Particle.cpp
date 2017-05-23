#include "stdafx.h"
#include "Particle.h"


Particle::Particle()
{
}

Particle::Particle(D3DXVECTOR3 iPos, D3DXVECTOR3 ivel,D3DXCOLOR icolor,int id): color(icolor)
{
	pos = iPos; txtid = id; velocity = ivel;
	acceleration.y = 0.18f;
	acceleration.x = 0;
	acceleration.z = 0;
	Volume.push_back(FRECT{ 0,0,2.5f,2.5f });

	Volume.push_back(FRECT{ 0,0,2.5f,2.5f });
}

RESULT Particle::UpdateSub()
{
	if (!IsInScreen()) return Destroy;
	return Default;
}
VOID Particle::SetComponent()
{
	ComponentList.push_back(new ParticlePhysicsComponent);
	ComponentList.push_back(new ParticleGraphicsComponent);
}

Particle::~Particle()
{
}
