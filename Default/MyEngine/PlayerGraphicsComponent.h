#pragma once
#include "GraphicsComponent.h"
class PlayerGraphicsComponent :
	public GraphicsComponent
{
public:
	virtual VOID Update(GameObject* pObj);
	PlayerGraphicsComponent();
	~PlayerGraphicsComponent();
};

