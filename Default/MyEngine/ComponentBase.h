#pragma once
#include "stdafx.h"

class ComponentBase
{

public:
	virtual VOID Update(GameObject* pObj) {}
	ComponentBase();
	virtual ~ComponentBase();
};

