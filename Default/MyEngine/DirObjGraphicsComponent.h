#pragma once
#include "GraphicsComponent.h"
class DirObjGraphicsComponent :
	public GraphicsComponent
{
public:
	DirObjGraphicsComponent();
	virtual VOID Update(GameObject * pObj);
	~DirObjGraphicsComponent();
};

