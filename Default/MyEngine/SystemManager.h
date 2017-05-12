#pragma once

#include "stdafx.h"
#include <list>
using namespace std;
class GameObject;
class SystemManager
{
private:
	std::list<GameObject*> ObjectList;
	static SystemManager* instance;
	SystemManager();
	HRESULT Initialize();
public:
	VOID Update();
	static SystemManager* GetInstance();
	~SystemManager();
};

