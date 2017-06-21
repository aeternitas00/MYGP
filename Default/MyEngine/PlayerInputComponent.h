#pragma once
#include "InputComponent.h"
class PlayerInputComponent :
	public InputComponent
{
public:
	PlayerInputComponent();
	~PlayerInputComponent();
	virtual RESULT Update(GameObject* pObj);
};

