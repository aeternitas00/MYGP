#pragma once

#include "stdafx.h"
#include <list>
using namespace std;
class GameObject;
class PlayerBullet;
class GameTerrain;
class SystemManager
{
private:
	std::list<GameObject*> ObjectList;
	std::list<PlayerBullet*> PlayerBulletList;
	std::list<Enemy*> EnemyList;
	std::list<GameTerrain*> TerrainList;
	int Stage;
	static SystemManager* instance;
	SystemManager();
	HRESULT Initialize();
public:
	VOID Update();
	static SystemManager* GetInstance();
	VOID AddPlayerBullet(PlayerBullet* pObj);
	VOID AddEnemy(Enemy * pObj);
	std::list<GameTerrain*> GetTerrainList() { return TerrainList; }
	~SystemManager();
};

