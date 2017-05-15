#pragma once
#include "GraphicsComponent.h"
class TerrainGraphicsComponent :
	public GraphicsComponent
{
public:
	TerrainGraphicsComponent();
	virtual ~TerrainGraphicsComponent();
	virtual VOID Update(GameObject* pObj);
};

