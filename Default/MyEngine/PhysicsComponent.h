#pragma once
#include "stdafx.h"

typedef struct __floatrect {
	float top, bottom, left, right;
}FRECT;
class PhysicsComponent:public ComponentBase
{
protected:
	FRECT volume;
public:
	PhysicsComponent();
	
	virtual VOID Update(GameObject* pObj);
	virtual ~PhysicsComponent();
};

