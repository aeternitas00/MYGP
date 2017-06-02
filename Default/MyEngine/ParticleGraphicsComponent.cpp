#include "stdafx.h"
#include "ParticleGraphicsComponent.h"


ParticleGraphicsComponent::ParticleGraphicsComponent()
{
}

VOID ParticleGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return;
	Particle* ptemp = dynamic_cast<Particle*>(pObj);
	if (ptemp == NULL) return;

	RenderManager::GetInstance()->DrawParticle(pObj->pos, pObj->txtid,ptemp->GetColor());
}


ParticleGraphicsComponent::~ParticleGraphicsComponent()
{
}
