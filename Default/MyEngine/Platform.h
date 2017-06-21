#pragma once
#include "GameObject.h"
class Platform :
	public GameObject
{
public:
	Platform();
	~Platform();
	VOID Initialize(char * n);
};

