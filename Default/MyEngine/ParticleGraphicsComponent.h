#pragma once
#include "GraphicsComponent.h"
class ParticleGraphicsComponent :
	public GraphicsComponent
{
public:
	ParticleGraphicsComponent();
	virtual VOID Update(GameObject* pObj);
	virtual ~ParticleGraphicsComponent();
};

