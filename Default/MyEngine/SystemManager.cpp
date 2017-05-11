#include "stdafx.h"
#include "SystemManager.h"

SystemManager* SystemManager::instance = nullptr;

VOID SystemManager::update()
{
	for(auto it: ObjectList) 
		it->update();
	return;
}

SystemManager * SystemManager::GetInstance()
{
	if (instance == NULL) {
		instance = new SystemManager();
		if (FAILED(instance->Initialize())) return nullptr;
	}
	return instance;
}

SystemManager::SystemManager()
{
	ObjectList.clear();
}

HRESULT SystemManager::Initialize()
{
	ObjectList.push_back(new Player());
	return S_OK;
}

SystemManager::~SystemManager()
{
}
