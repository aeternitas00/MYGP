#pragma once
#include "GraphicsComponent.h"
class TerrainGraphicsComponent :
	public GraphicsComponent
{
public:
	TerrainGraphicsComponent();
	virtual ~TerrainGraphicsComponent();
	virtual RESULT Update(GameObject* pObj);
};

