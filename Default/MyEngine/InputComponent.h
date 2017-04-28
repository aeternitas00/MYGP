#pragma once
#include "stdafx.h"
class InputComponent:public ComponentBase
{
private:
	float velocity;
	float acceleration;
public:
	InputComponent();
	virtual VOID update(GameObject& rObj);
	virtual ~InputComponent();
};

