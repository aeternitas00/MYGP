#include "stdafx.h"
#include "ParticleGraphicsComponent.h"


ParticleGraphicsComponent::ParticleGraphicsComponent()
{
}

RESULT ParticleGraphicsComponent::Update(GameObject * pObj)
{
	if (pObj->txtid == -1) return Default;
	Particle* ptemp = dynamic_cast<Particle*>(pObj);
	if (ptemp == NULL) return Default;

	RenderManager::GetInstance()->DrawParticle(pObj->pos, pObj->txtid,ptemp->GetColor());
	return Default;
}


ParticleGraphicsComponent::~ParticleGraphicsComponent()
{
}
