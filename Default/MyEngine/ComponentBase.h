#pragma once
#include "stdafx.h"

class ComponentBase
{
public:
	virtual VOID update()=0;
	ComponentBase();
	virtual ~ComponentBase();
};

