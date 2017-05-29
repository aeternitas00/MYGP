#pragma once
#include "ComponentBase.h"
class GraphicsComponent :
	public ComponentBase
{
protected:
	D3DXMATRIX mat;
public:
	GraphicsComponent();
	virtual VOID Update(GameObject* pObj);
	virtual ~GraphicsComponent();
};

