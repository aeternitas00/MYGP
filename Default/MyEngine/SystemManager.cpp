#include "stdafx.h"
#include "SystemManager.h"

SystemManager* SystemManager::instance = nullptr;

VOID SystemManager::Update()
{
	
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
		case OutOfScreen:
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
	for (auto it = EnemyBulletList.begin(); it != EnemyBulletList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it;
			EnemyBulletList.erase(it++);
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

	for (auto it = ObstacleList.begin(); it != ObstacleList.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it;
			ObstacleList.erase(it++);
			break;
		}
	}
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
	if (MyPlayer != NULL) {
		switch (MyPlayer->Update())
		{
		case Destroy:
			delete MyPlayer;
			MyPlayer = NULL;
			break;
		}
	}

	if (DelayedMessage != -1)
	{
		MoveScene(DelayedMessage);
		DelayedMessage = -1;
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

VOID SystemManager::AddObject(GameObject* pObj)
{
	ObjectList.push_back(pObj);
	ObjectList.back()->SetComponent();
}

SystemManager::SystemManager() :DelayedMessage(-1),CurrentSFNo(1)
{
	ObjectList.clear();
}

HRESULT SystemManager::Initialize()
{
	SetupStage(1);
	SetupScene(0);
	return S_OK;
}

VOID SystemManager::LoadSF()
{
	wstring path(L"Savefile");
	path += std::to_wstring(CurrentSFNo) + L".txt";
	ifstream inFile;
	inFile.open(path,ifstream::in);
	char mystr[200], *temp = NULL;
	inFile.getline(mystr, 200);
	int x = atoi(strtok_s(mystr, " ", &temp));
	int y = atoi(strtok_s(NULL, " ", &temp));
	SetPlayer(x, y);
	
	for (auto it = ObjectList.begin(); it != ObjectList.end();) {
			delete *it; ObjectList.erase(it++);
	}
	for (auto it = EnemyBulletList.begin(); it != EnemyBulletList.end();) {
		delete *it; EnemyBulletList.erase(it++);
	}
	for (auto it = PlayerBulletList.begin(); it != PlayerBulletList.end();) {
		delete *it; PlayerBulletList.erase(it++);
	}
	for (auto it = ObstacleList.begin(); it != ObstacleList.end();) {
		delete *it; ObstacleList.erase(it++);
	}
	for (auto it = TerrainList.begin(); it != TerrainList.end();) {
		delete *it; TerrainList.erase(it++);
	}
	for (auto it = EnemyList.begin(); it != EnemyList.end();) {
		delete *it; EnemyList.erase(it++);
	}


	inFile.getline(mystr, 200);
	x = atoi(strtok_s(mystr, " ", &temp));
	y = atoi(strtok_s(NULL, " ", &temp));
	SetupStage(x);	SetupScene(y);
	inFile.close();
}

VOID SystemManager::SaveSF()
{
	wstring path(L"Savefile");
	path += std::to_wstring(CurrentSFNo) + L".txt";
	ofstream outFile;

	outFile.close();
}

VOID SystemManager::SetupStage(int i)
{
	CurrentStage = { L"Stage"+ std::to_wstring(i),-1 };
	wstring path(CurrentStage.path);
	path += L"-" + std::to_wstring(0) + L".txt";
	ifstream inFile(path);
  	char str[200], *temp = NULL;
	inFile.getline(str, 200);
	CurrentStage.bgid = atoi(strtok_s(str, " ", &temp));
	inFile.getline(str, 200);
	int x = atoi(strtok_s(str, " ", &temp));
	int y = atoi(strtok_s(NULL, " ", &temp));
	SetPlayer(x, y);
	inFile.close();

}

VOID SystemManager::SetupScene(int i)
{
	CurrentScene = { i, };
	wstring path(CurrentStage.path);

	path += L"-" + std::to_wstring(i) + L".txt";
	ifstream inFile(path);

	char str[200];
	char* temp = NULL, *token = NULL;

	if (i == 0)
	{
		inFile.getline(str, 200);
		inFile.getline(str, 200);

	}

	inFile.getline(str, 200);
	CurrentScene.connected[0] = atoi(strtok_s(str, " ", &temp));
	CurrentScene.connected[1] = atoi(strtok_s(NULL, " ", &temp));
	CurrentScene.connected[2] = atoi(strtok_s(NULL, " ", &temp));
	CurrentScene.connected[3] = atoi(strtok_s(NULL, " ", &temp));

	for (auto it = ObstacleList.begin(); it != ObstacleList.end();) {
		delete *it; ObstacleList.erase(it++);
	}
	for (auto it = TerrainList.begin(); it != TerrainList.end();) {
		delete *it; TerrainList.erase(it++);
	}
	for (auto it = EnemyList.begin(); it != EnemyList.end();) {
		delete *it; EnemyList.erase(it++);
	}

	inFile.getline(str, 200);
	token = strtok_s(str, " ", &temp);
	while (token) {
		int var = atoi(token);
		int type;
		switch (var) {
		case 1:
			type = atoi(strtok_s(NULL, " ", &temp));
			for (int num = atoi(strtok_s(NULL, " ", &temp)); num > 0; num--) {
				inFile.getline(str, 200);
				int x = atoi(strtok_s(str, " ", &temp));
				int y = atoi(strtok_s(NULL, " ", &temp));
				int width = atoi(strtok_s(NULL, " ", &temp));
				int height = atoi(strtok_s(NULL, " ", &temp));
				bool ctab = atoi(strtok_s(NULL, " ", &temp));
				TerrainList.push_back(new GameTerrain(D3DXVECTOR3(x, y, 0), width, height, type, ctab));
				TerrainList.back()->SetComponent();
			}
			break;
		case 2:
			for (int num = atoi(strtok_s(NULL, " ", &temp)); num > 0; num--) {
				inFile.getline(str, 200);
				float x = atoi(strtok_s(str, " ", &temp));
				float y = atoi(strtok_s(NULL, " ", &temp));
				TerrainList.push_back(new GameTerrain(D3DXVECTOR3(x, y, 0),1,1,TXTID_MISSILE_LBASE,false));
				TerrainList.back()->SetComponent();
				EnemyList.push_back(new MissileLauncher(D3DXVECTOR3(x,y,0)));
				EnemyList.back()->SetComponent();
			}
			break;
		case 3:
			for (int num = atoi(strtok_s(NULL, " ", &temp)); num > 0; num--) {
				inFile.getline(str, 200);
				float x = atoi(strtok_s(str, " ", &temp));
				float y = atoi(strtok_s(NULL, " ", &temp));
				float dir = atoi(strtok_s(NULL, " ", &temp));
				ObstacleList.push_back(new Spike(D3DXVECTOR3(x, y, 0),TXTID_SPIKE,dir));
				ObstacleList.back()->SetComponent();
			}
			break;
		default:
			break;
		}
		inFile.getline(str, 200);
		token = strtok_s(str, " ", &temp);
	}
	inFile.close();
}

VOID SystemManager::SetPlayer(float x, float y)
{
	if (MyPlayer == nullptr) {
		MyPlayer = new Player(D3DXVECTOR3(x, y, 0));
		MyPlayer->SetComponent();
	}
	else { MyPlayer->pos.x = x;
	MyPlayer->pos.y = y;
	MyPlayer->SetRemainJump(1);
	MyPlayer->SetTxt(TXTID_PLAYER);
	}
}

bool SystemManager::IsMovableSideOfScene(int side)
{
	return (CurrentScene.connected[side] != -1);
}

VOID SystemManager::MoveScene(int toside)
{
	if (CurrentScene.connected[toside] != -1 || CurrentScene.connected[toside] != CurrentScene.sno)
	{
		SetupScene(CurrentScene.connected[toside]);

		for (auto it = EnemyBulletList.begin(); it != EnemyBulletList.end();) 
			(*it)->UpdateByMovingScene(toside);
	}
}

SystemManager::~SystemManager()
{
}
