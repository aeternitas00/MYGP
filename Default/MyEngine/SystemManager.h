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



class ListBase {};

template <class T>
class ListChild :public ListBase {
private:
	std::list<T> list;
public:
	void add(GameObject* temp, const char* n);
	void clear();
	void update();
private:
	RESULT updateobj(GameObject*);
};

using ListAs = std::map<std::string, ListBase*>;

template <class T> void constructor(ListBase* as)
{ 
	static_cast<ListChild<T*>*>(as)->add(new T(),"");
}

class myfactory
{
private:
	typedef void(*constructor_t)(ListBase*);
	typedef std::map<std::string, constructor_t> map_type;
	
	map_type m_classes;
	ListAs m_mylistas;
public:
	myfactory();

	template <class T>
	void register_class(std::string const& n);
	template <class T>
	void clearlist(std::string const& n);
	template<class T>
	void updatelist(std::string const& n);
	void construct(std::string const& n);

};

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

	myfactory* m_factory;

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

