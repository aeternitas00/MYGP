#pragma once
#include "stdafx.h"
class InputComponent:public ComponentBase
{
private:

public:
	InputComponent();
	virtual VOID Update(GameObject& rObj);
	virtual ~InputComponent();
};

