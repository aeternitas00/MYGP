#pragma once
#include "stdafx.h"
class InputComponent:public ComponentBase
{
private:

public:
	InputComponent();
	virtual VOID update(GameObject& rObj);
	virtual ~InputComponent();
};

