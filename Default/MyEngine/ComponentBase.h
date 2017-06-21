#pragma once
#include "stdafx.h"

class ComponentBase
{

public:
	virtual RESULT Update(GameObject* pObj) { return Default; }
	ComponentBase();
	virtual ~ComponentBase();
};

