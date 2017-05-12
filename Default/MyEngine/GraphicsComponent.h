#pragma once
#include "ComponentBase.h"
class GraphicsComponent :
	public ComponentBase
{
public:
	GraphicsComponent();
	virtual VOID Update(GameObject& rObj);
	virtual ~GraphicsComponent();
};

