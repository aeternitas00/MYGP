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
class SavePoint;
typedef struct __stageinfo {
	wstring path;
	int bgid;
	int no;
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
	std::list<SavePoint*> SavePointList;
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
	VOID AddEnemyBullet(EnemyBullet * pObj);
	int GetCurrentBGID() { return CurrentStage.bgid; }
	Player* GetPlayer() { return MyPlayer; }
	std::list<GameObject*> GetObjectList() { return ObjectList; }
	std::list<GameTerrain*> GetTerrainList() { return TerrainList; }
	std::list<Obstacle*> GetObstacleList() { return ObstacleList; }
	std::list<Enemy*> GetEnemyList() { return EnemyList; }
	std::list<SavePoint*> GetSavePointList() { return SavePointList; }
	std::list<EnemyBullet*> GetEnemyBulletList() {	return EnemyBulletList;	}
	VOID LoadSF();
	VOID ClearObjects();
	VOID SaveSF();

	VOID SetupTitleScreen();
	
	VOID SetupStage(int i);
	VOID SetupStage(int i, bool reset);
	VOID SetupScene(int i);
	VOID SetPlayer(float,float);
	VOID SendMoveSceneMessage(int side) { DelayedMessage = side; }
	bool IsMovableSideOfScene(int side);
	VOID MoveScene(int toside);
	~SystemManager();
};

