#pragma once
#include "stdafx.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
class InputComponent:public ComponentBase
{
private:

public:
	InputComponent();
	virtual RESULT Update(GameObject* pObj);
	virtual ~InputComponent();
};

