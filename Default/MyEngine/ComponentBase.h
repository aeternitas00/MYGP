#pragma once
#include "stdafx.h"

class ComponentBase
{
protected:
	D3DXMATRIX mat;
public:
	virtual VOID Update(GameObject* pObj) {}
	ComponentBase();
	virtual ~ComponentBase();
};

