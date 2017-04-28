#pragma once
#include "stdafx.h"

class Player :
	public GameObject
{
private:
	RECT volume;	


public:
	Player();
	virtual ~Player();
};

