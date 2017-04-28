#pragma once
#include "ComponentBase.h"
class GraphicsComponent :
	public ComponentBase
{
public:
	GraphicsComponent();
	virtual VOID update(GameObject& rObj);
	virtual ~GraphicsComponent();
};

