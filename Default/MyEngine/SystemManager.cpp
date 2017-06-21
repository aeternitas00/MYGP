#include "stdafx.h"
#include "SystemManager.h"
#include "Factory.h"
#include "ListClass.h"

SystemManager* SystemManager::instance = nullptr;

myfactory * SystemManager::GetFactory() { return m_factory; }

VOID SystemManager::Update()
{
	UPDATE_LIST(GameTerrain);
	UPDATE_LIST(GameObject);
	UPDATE_LIST(Obstacle);
	UPDATE_LIST(Enemy);
	UPDATE_LIST(SavePoint);
	UPDATE_LIST(PlayerBullet);
	UPDATE_LIST(EnemyBullet);

	if (MyPlayer != NULL) {
		switch (MyPlayer->Update())
		{
		case Destroy:
			delete MyPlayer;
			MyPlayer = NULL;
			break;
		}
	}

	if (DelayedMessage<=3&&DelayedMessage>=0)
	{
		MoveScene(DelayedMessage);
		DelayedMessage = -1;
	}
	else if (DelayedMessage >= 4 && DelayedMessage <= 6) {
		CurrentSFNo = DelayedMessage - 3;
		LoadSF();
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
	pObj->SetComponent();
	GET_LIST_IN(PlayerBullet)->push_back(pObj);
}

VOID SystemManager::AddEnemy(Enemy* pObj)
{
	pObj->SetComponent();
	GET_LIST_IN(Enemy)->push_back(pObj);
}

VOID SystemManager::AddObject(GameObject* pObj)
{
	pObj->SetComponent();
	GET_LIST_IN(GameObject)->push_back(pObj);
}

VOID SystemManager::AddEnemyBullet(EnemyBullet * pObj)
{
	pObj->SetComponent();
	GET_LIST_IN(EnemyBullet)->push_back(pObj);
}

SystemManager::SystemManager() :DelayedMessage(-1),CurrentSFNo(1),CurrentStage(StageInfo{L"",-1,-1})
{
}


HRESULT SystemManager::Initialize()
{
	m_factory = new myfactory();

	REGISTER_CLASS(GameObject);
	REGISTER_CLASS(GameTerrain);
	REGISTER_CLASS(EnemyBullet);
	REGISTER_CLASS(PlayerBullet);
	REGISTER_CLASS(Obstacle);
	REGISTER_CLASS(Enemy);
	REGISTER_CLASS(SavePoint);
	REGISTER_CLASS_SUB(BulletGenerator, GameObject);
	REGISTER_CLASS_SUB(Spike, Obstacle);
	REGISTER_CLASS_SUB(Boss, Enemy);
	SetupTitleScreen();

	SoundManager::GetInstance()->PlayWaveFilePos(SOUND_INTROBGM,30000);
	SoundManager::GetInstance()->PlayWaveFileLoop(SOUND_INTROTD);
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
	CLEAR_LIST(GameObject);
	CLEAR_LIST(GameTerrain);
	CLEAR_LIST(EnemyBullet);
	CLEAR_LIST(PlayerBullet);
	CLEAR_LIST(Obstacle);
	CLEAR_LIST(Enemy);
	CLEAR_LIST(SavePoint);
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
	AddObject(new GameObject(D3DXVECTOR3(-47,MAX_Y-84,0), TXTID_INTROBLK1));
	AddObject(new GameObject(D3DXVECTOR3(435, -174, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(467, -174, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(499, -174, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(435, -206, 0), TXTID_INTROKID));
	AddObject(new GameObject(D3DXVECTOR3(467, -142, 0), TXTID_INTROBLK3));
	AddObject(new GameObject(D3DXVECTOR3(499, -142, 0), TXTID_INTROBLK3));
	AddObject(new Spike(D3DXVECTOR3(467, -110, 0), TXTID_SPIKE, 1));
	AddObject(new Spike(D3DXVECTOR3(499, -206, 0), TXTID_SPIKE, 0));
	AddObject(new GameObject(D3DXVECTOR3(130, -700, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(194, -732, 0), TXTID_INTROKID2));
	AddObject(new GameObject(D3DXVECTOR3(162, -700, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(194, -700, 0), TXTID_INTROBLK2));
	AddObject(new GameObject(D3DXVECTOR3(130, -668, 0), TXTID_INTROBLK3));
	AddObject(new GameObject(D3DXVECTOR3(162, -668, 0), TXTID_INTROBLK3));
	AddObject(new Spike(D3DXVECTOR3(162, -632, 00), TXTID_SPIKE, 1));
	AddObject(new Spike(D3DXVECTOR3(130, -732, 0), TXTID_SPIKE, 0));
	AddObject(new IntroCharacter());
}

VOID SystemManager::SetupStage(int i)
{
	RenderManager::GetInstance()->IncludeTexture(i);
	SoundManager::GetInstance()->UpdateStageList(i);
	SoundManager::GetInstance()->StopWaveFile();
	SoundManager::GetInstance()->PlayWaveFileLoop(0);
	SoundManager::GetInstance()->PlayWaveFile(SOUND_BOSHYTIME);
	CurrentStage = { L"Stage" + std::to_wstring(i) + L"/StageInfo" + std::to_wstring(i),-1,i };
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
	RenderManager::GetInstance()->IncludeTexture(i);
	SoundManager::GetInstance()->UpdateStageList(i);
	SoundManager::GetInstance()->StopWaveFile();
	SoundManager::GetInstance()->PlayWaveFileLoop(0);
	SoundManager::GetInstance()->PlayWaveFile(SOUND_BOSHYTIME);
	CurrentStage = { L"Stage" + std::to_wstring(i)+L"/StageInfo" + std::to_wstring(i),-1,i };
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

	if (i == 100) // BOSS
	{
		inFile.getline(str, 200);
		inFile.getline(str, 200);
		int x = atoi(strtok_s(str, " ", &temp));
		int y = atoi(strtok_s(NULL, " ", &temp));
		SetPlayer(x, y);
	}

	inFile.getline(str, 200);
	CurrentScene.connected[0] = atoi(strtok_s(str, " ", &temp));
	CurrentScene.connected[1] = atoi(strtok_s(NULL, " ", &temp));
	CurrentScene.connected[2] = atoi(strtok_s(NULL, " ", &temp));
	CurrentScene.connected[3] = atoi(strtok_s(NULL, " ", &temp));

	CLEAR_LIST(GameObject);
	CLEAR_LIST(GameTerrain);
	CLEAR_LIST(Enemy);
	CLEAR_LIST(PlayerBullet);
	CLEAR_LIST(SavePoint);
	CLEAR_LIST(Obstacle);


	inFile.getline(str, 200);
	token = strtok_s(str, " ", &temp);
	while (token) {
		if (strlen(token) > 2){
			string type(token);
			for (int num = atoi(strtok_s(NULL, " ", &temp)); num > 0; num--) {
				inFile.getline(str, 200);
				m_factory->construct(type,str);
			}
			inFile.getline(str, 200);
			token = strtok_s(str, " ", &temp); 
			continue;
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

		for (auto it:*GET_LIST_IN(EnemyBullet)) 
			it->UpdateByMovingScene(toside);

	}
}

SystemManager::~SystemManager()
{
}
