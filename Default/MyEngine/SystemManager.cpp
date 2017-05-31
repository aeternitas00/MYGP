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

	UpdateThisList(EnemyList);
	UpdateThisList(TerrainList);
	UpdateThisList(ObstacleList);
	UpdateThisList(SavePointList);
	UpdateThisList(ObjectList);

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
		case OutOfScreen:
			delete *it;
			EnemyBulletList.erase(it++);
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

template<typename T>
VOID SystemManager::ClearThisList(std::list<T>& ilist)
{
	for (auto it = ilist.begin(); it != ilist.end();) {
		delete *it; ilist.erase(it++);
	}
}

template<typename T>
VOID SystemManager::UpdateThisList(std::list<T>& ilist)
{
	for (auto it = ilist.begin(); it != ilist.end();) {
		switch ((*it)->Update())
		{
		case Default:
			it++;
			break;
		case Destroy:
			delete *it;
			ilist.erase(it++);
			break;
		}
	}
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

VOID SystemManager::AddEnemyBullet(EnemyBullet * pObj)
{
	EnemyBulletList.push_back(pObj);
	EnemyBulletList.back()->SetComponent();
}

SystemManager::SystemManager() :DelayedMessage(-1),CurrentSFNo(1),CurrentStage(StageInfo{L"",-1,-1})
{
	ObjectList.clear();
}

HRESULT SystemManager::Initialize()
{
	/*SetupTitleScreen();*/
	RenderManager::GetInstance()->IncludeTexture(1);
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
	
	ClearObjects();
	inFile.getline(mystr, 200);
	x = atoi(strtok_s(mystr, " ", &temp));
	y = atoi(strtok_s(NULL, " ", &temp));
	SetupStage(x,false);	SetupScene(y);
	inFile.close();
}

VOID SystemManager::ClearObjects()
{
	ClearThisList(ObjectList);
	ClearThisList(EnemyBulletList);
	ClearThisList(PlayerBulletList);
	ClearThisList(ObstacleList);
	ClearThisList(TerrainList);
	ClearThisList(EnemyList);
	ClearThisList(SavePointList);
}

VOID SystemManager::SaveSF()
{
	wstring path(L"Savefile");
	path += std::to_wstring(CurrentSFNo) + L".txt";
	ofstream outFile;
	outFile.open(path, ofstream::out);
	string OK;

	OK += std::to_string(int(MyPlayer->pos.x)) + " " +std::to_string(int(MyPlayer->pos.y));
	OK += "\n";
	OK += std::to_string(CurrentStage.no) + " " + std::to_string(CurrentScene.sno);

	outFile << OK << endl;
	outFile.close();
}


VOID SystemManager::SetupTitleScreen()
{
	ClearObjects();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(-47,MAX_Y-84,0), TXTID_INTROBLK1));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(425, -124, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(457, -124, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(489, -124, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(425, -156, 0), TXTID_INTROKID));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(457, -92, 0), TXTID_INTROBLK3));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(489, -92, 0), TXTID_INTROBLK3));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new Spike(D3DXVECTOR3(457, -60, 0), TXTID_INTROKID2+1, 1));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new Spike(D3DXVECTOR3(489, -156, 0), TXTID_INTROKID2+1, 0));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(130, -670, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(194, -702, 0), TXTID_INTROKID2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(162, -670, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(194, -670, 0), TXTID_INTROBLK2));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(130, -638, 0), TXTID_INTROBLK3));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new GameObject(D3DXVECTOR3(162, -638, 0), TXTID_INTROBLK3));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new Spike(D3DXVECTOR3(162, -602, 00), TXTID_INTROKID2 + 1, 1));
	ObjectList.back()->SetComponent();
	ObjectList.push_back(new Spike(D3DXVECTOR3(130, -702, 0), TXTID_INTROKID2 + 1, 0));
	ObjectList.back()->SetComponent();

	ObjectList.push_back(new IntroCharacter());
	ObjectList.back()->SetComponent();
}

VOID SystemManager::SetupStage(int i)
{
	CurrentStage = { L"Stage"+ std::to_wstring(i),-1,i };
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

VOID SystemManager::SetupStage(int i,bool reset)
{
	CurrentStage = { L"Stage" + std::to_wstring(i),-1,i };
	wstring path(CurrentStage.path);
	path += L"-" + std::to_wstring(0) + L".txt";
	ifstream inFile(path);
	char str[200], *temp = NULL;
	inFile.getline(str, 200);
	CurrentStage.bgid = atoi(strtok_s(str, " ", &temp));
	if (reset) {
		inFile.getline(str, 200);
		int x = atoi(strtok_s(str, " ", &temp));
		int y = atoi(strtok_s(NULL, " ", &temp));
		SetPlayer(x, y);
	}
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

	ClearThisList(ObstacleList);
	ClearThisList(PlayerBulletList);
	ClearThisList(TerrainList);
	ClearThisList(EnemyList);
	ClearThisList(SavePointList);

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
		case 4:
			for (int num = atoi(strtok_s(NULL, " ", &temp)); num > 0; num--) {
				inFile.getline(str, 200);
				float x = atoi(strtok_s(str, " ", &temp));
				float y = atoi(strtok_s(NULL, " ", &temp));
				SavePointList.push_back(new SavePoint(D3DXVECTOR3(x, y, 0)));
				SavePointList.back()->SetComponent();
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
	else { 
		MyPlayer->pos.x = x;
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

		for (auto it:EnemyBulletList) 
			it->UpdateByMovingScene(toside);

	}
}

SystemManager::~SystemManager()
{
}
