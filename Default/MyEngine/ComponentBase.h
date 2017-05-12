#pragma once
#include "stdafx.h"

class ComponentBase
{
public:
	virtual VOID Update(GameObject& rObj)=0;
	ComponentBase();
	virtual ~ComponentBase();
};

