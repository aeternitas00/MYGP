#include "stdafx.h"
#include "SystemManager.h"

SystemManager* SystemManager::instance = nullptr;

VOID SystemManager::Update()
{
	for (auto it = ObjectList.begin(); it != ObjectList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it; ObjectList.erase(it++);
			break;
		}
	}
	for (auto it = PlayerBulletList.begin(); it != PlayerBulletList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it; 
			PlayerBulletList.erase(it++);
			break;
		}
	}
	for (auto it = EnemyList.begin(); it != EnemyList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it;
			EnemyList.erase(it++);
			break;
		}
	}
	for (auto it = TerrainList.begin(); it != TerrainList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it;
			TerrainList.erase(it++);
			break;
		}
	}
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

VOID SystemManager::AddPlayerBullet(PlayerBullet* pObj)
{
	PlayerBulletList.push_back(pObj);
	PlayerBulletList.back()->SetComponent();
}

VOID SystemManager::AddEnemy(Enemy* pObj)
{
	EnemyList.push_back(pObj);
	EnemyList.back()->SetComponent();
}

SystemManager::SystemManager()
{
	ObjectList.clear();
}

HRESULT SystemManager::Initialize()
{
	ObjectList.push_back(new Player());
	ObjectList.back()->SetComponent();
	TerrainList.push_back(new GameTerrain(D3DXVECTOR3(50,394,0),10,1,TXTID_BLOCK_CM));
	TerrainList.back()->SetComponent();
	TerrainList.push_back(new GameTerrain(D3DXVECTOR3(200, 332,0), 5, 1, TXTID_BLOCK_CM));
	TerrainList.back()->SetComponent();

	return S_OK;
}

SystemManager::~SystemManager()
{
}
