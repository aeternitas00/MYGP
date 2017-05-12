#pragma once
#include "stdafx.h"

typedef struct PLAYER_STATUS{
	// jump bool whatever;
};

class Player :
	public GameMovableObject
{
private:

public:
	Player();
	~Player();
	virtual VOID SetComponent();
};

