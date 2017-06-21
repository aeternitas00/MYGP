#pragma once
#include "GraphicsComponent.h"
class PlayerGraphicsComponent :
	public GraphicsComponent
{
public:
	virtual RESULT Update(GameObject* pObj);
	PlayerGraphicsComponent();
	~PlayerGraphicsComponent();
};

