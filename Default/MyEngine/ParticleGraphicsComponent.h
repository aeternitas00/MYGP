#pragma once
#include "GraphicsComponent.h"
class ParticleGraphicsComponent :
	public GraphicsComponent
{
public:
	ParticleGraphicsComponent();
	virtual RESULT Update(GameObject* pObj);
	virtual ~ParticleGraphicsComponent();
};

