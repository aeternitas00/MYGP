#pragma once
#include "stdafx.h"

class ComponentBase
{
public:
	virtual VOID update(GameObject& rObj)=0;
	ComponentBase();
	virtual ~ComponentBase();
};

