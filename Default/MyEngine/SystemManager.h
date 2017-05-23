#pragma once

#include "stdafx.h"
#include <list>
#include <fstream>
using namespace std;
class GameObject;
class PlayerBullet;
class GameTerrain;
class Enemy;
class EnemyBullet;
class Player;
class Obstacle;
typedef struct __stageinfo {
	wstring path;
	int bgid;
}StageInfo;
typedef struct __sceneinfo {
	int sno;
	int connected[4];// 0 up 1 down 2 left 3 right
}SceneInfo;
enum Connected {
	CToUp,CToDown,CToLeft,CToRight
};
class SystemManager
{
private:
	std::list<GameObject*> ObjectList;
	std::list<PlayerBullet*> PlayerBulletList;
	std::list<Enemy*> EnemyList;
	std::list<EnemyBullet*> EnemyBulletList;
	std::list<Obstacle*> ObstacleList;
	std::list<GameTerrain*> TerrainList;
	Player* MyPlayer;
	StageInfo CurrentStage;
	SceneInfo CurrentScene;
	int DelayedMessage;
	short CurrentSFNo;
	static SystemManager* instance;
	SystemManager();
	HRESULT Initialize();
public:
	VOID Update();
	static SystemManager* GetInstance();
	VOID AddPlayerBullet(PlayerBullet* pObj);
	VOID AddEnemy(Enemy * pObj);
	VOID AddObject(GameObject * pObj);
	int GetCurrentBGID() { return CurrentStage.bgid; }
	std::list<GameTerrain*> GetTerrainList() { return TerrainList; }
	std::list<Obstacle*> GetObstacleList() { return ObstacleList; }

	VOID LoadSF();
	VOID SaveSF();
	
	VOID SetupStage(int i);
	VOID SetupScene(int i);
	VOID SetPlayer(float,float);
	VOID SendMoveSceneMessage(int side) { DelayedMessage = side; }
	bool IsMovableSideOfScene(int side);
	VOID MoveScene(int toside);
	~SystemManager();
};

