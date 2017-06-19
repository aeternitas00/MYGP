#pragma once

#include "stdafx.h"
#include "Factory.h"
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

class ListBase;


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
	//std::list<GameObject*> ObjectList;
	//std::list<PlayerBullet*> PlayerBulletList;
	//std::list<Enemy*> EnemyList;
	//std::list<EnemyBullet*> EnemyBulletList;
	//std::list<Obstacle*> ObstacleList;
	//std::list<GameTerrain*> TerrainList;
	//std::list<SavePoint*> SavePointList;

	Player* MyPlayer;

	StageInfo CurrentStage;
	SceneInfo CurrentScene;

	int DelayedMessage;
	short CurrentSFNo;
	static SystemManager* instance;
	SystemManager();
	HRESULT Initialize();

	myfactory* m_factory;

public:
	myfactory* GetFactory();
	VOID Update();
	static SystemManager* GetInstance();
	VOID AddPlayerBullet(PlayerBullet* pObj);
	VOID AddEnemy(Enemy * pObj);
	VOID AddObject(GameObject * pObj);
	VOID AddEnemyBullet(EnemyBullet * pObj);
	int GetCurrentBGID() { return CurrentStage.bgid; }

	Player* GetPlayer() { return MyPlayer; }

	VOID LoadSF();
	VOID ClearObjects();
	VOID SaveSF();
	VOID SetSFNo(int i) { CurrentSFNo = i; }

	template <typename T>
	VOID ClearThisList(std::list<T> &ilist);
	template <typename T>
	VOID UpdateThisList(std::list<T> &ilist);

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

#define GET_SYSMANAGER() SystemManager::GetInstance()

#define REGISTER_CLASS(n) GetFactory()->register_class<n>(#n)
#define GET_LIST_IN(n) GetFactory()->get_list<n>(#n)
#define GET_LIST_OUT(n) SystemManager::GetInstance()->GetFactory()->get_list<n>(#n)
#define UPDATE_LIST(n) GetFactory()->update_list<n>(#n)
#define CLEAR_LIST(n) GetFactory()->clear_list<n>(#n)
#define REGISTER_CLASS_SUB(n,m) GetFactory()->register_class_sub<n>(#n,#m)