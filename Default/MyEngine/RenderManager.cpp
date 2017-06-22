#include "stdafx.h"
#include "RenderManager.h"
#include <sstream>
RenderManager* RenderManager::instance = NULL;

RenderManager::RenderManager()
{
	shaketimer = 0;
	shakescale = 0;
}

RenderManager* RenderManager::GetInstance()
{
	if (instance == NULL) {
		instance = new RenderManager();
		if (FAILED(instance->Initialize())) return nullptr;
	}
	return instance;
}

RenderManager::~RenderManager()
{

	if (m_pD3DDevice != NULL)
		m_pD3DDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();

	delete m_GeneralTextureList;
	delete m_StageTextureList;
	delete instance;
}

HRESULT RenderManager::Initialize()
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *GameRoot::GetInstance()->GetHwnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) return E_FAIL;

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	if (FAILED(IncludeTexture()))return E_FAIL;

	D3DXMatrixTranslation(&m_WorldMat, NULL, NULL, 0.0);

	return S_OK;
}

HRESULT RenderManager::IncludeTexture()
{
	wstring pathq(L"General/");

	ifstream inFile(pathq+L"General.txt");
	char strasd[200], *tempasd = NULL;
	inFile.getline(strasd, 200);

	int lenq = atoi(strasd);
	m_GeneralTextureList = new TEXTURESET[lenq];

	for (int i = 0; lenq > i; i++)
	{
		inFile.getline(strasd, 200);
		strtok_s(strasd, " ", &tempasd);
		
		wchar_t* pStr;
		int strSize = MultiByteToWideChar(CP_ACP, 0, strasd, -1, NULL, NULL);
		pStr = new WCHAR[strSize];
		MultiByteToWideChar(CP_ACP, 0, strasd, strlen(strasd) + 1, pStr, strSize);
		wstring pathtemp(pathq+pStr);

		m_GeneralTextureList[i].sizex = atoi(strtok_s(NULL, " ", &tempasd));
		m_GeneralTextureList[i].sizey = atoi(strtok_s(NULL, " ", &tempasd));
		m_GeneralTextureList[i].spfx = atoi(strtok_s(NULL, " ", &tempasd));
		m_GeneralTextureList[i].spfy = atoi(strtok_s(NULL, " ", &tempasd));

		string hex(strtok_s(NULL, " ", &tempasd));
		if(hex[0]=='0'&&'x'){ std::stringstream ss(hex); ss >> std::hex >> m_GeneralTextureList[i].bgc;}
		else { 
			int r=atoi(strtok_s(NULL, " ", &tempasd)); 
			int g = atoi(strtok_s(NULL, " ", &tempasd));
			int b = atoi(strtok_s(NULL, " ", &tempasd));
			m_GeneralTextureList[i].bgc = D3DCOLOR_XRGB(r, g, b);
		}
		
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3DDevice,pathtemp.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001
			, 0x0000001, m_GeneralTextureList[i].bgc, NULL, NULL, &m_GeneralTextureList[i].txt)))
		{
			wstring tempc = L"Could not find ";
			tempc += pathtemp;
			MessageBox(NULL, tempc.c_str(), L"Textures.exe", MB_OK);
			return E_FAIL;
		}
		delete pStr;
	}
	inFile.close();

	pathq = L"Intro/";
	inFile.open(pathq + L"Intro.txt");
	inFile.getline(strasd, 200);

	lenq = atoi(strasd);
	m_StageTextureList = new TEXTURESET[lenq];

	for (int i = 0; lenq > i; i++)
	{
		inFile.getline(strasd, 200);
		strtok_s(strasd, " ", &tempasd);

		wchar_t* pStr;
		int strSize = MultiByteToWideChar(CP_ACP, 0, strasd, -1, NULL, NULL);
		pStr = new WCHAR[strSize];
		MultiByteToWideChar(CP_ACP, 0, strasd, strlen(strasd) + 1, pStr, strSize);
		wstring pathtemp(pathq + pStr);

		m_StageTextureList[i].sizex = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].sizey = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].spfx = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].spfy = atoi(strtok_s(NULL, " ", &tempasd));

		string hex(strtok_s(NULL, " ", &tempasd));
		if (hex[0] == '0'&&'x') { std::stringstream ss(hex); ss >> std::hex >> m_StageTextureList[i].bgc; }
		else {
			int r = atoi(strtok_s(NULL, " ", &tempasd));
			int g = atoi(strtok_s(NULL, " ", &tempasd));
			int b = atoi(strtok_s(NULL, " ", &tempasd));
			m_StageTextureList[i].bgc = D3DCOLOR_XRGB(r, g, b);
		}

		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3DDevice, pathtemp.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001
			, 0x0000001, m_StageTextureList[i].bgc, NULL, NULL, &m_StageTextureList[i].txt)))
		{
			wstring tempc = L"Could not find ";
			tempc += pathtemp;
			MessageBox(NULL, tempc.c_str(), L"Textures.exe", MB_OK);
			return E_FAIL;
		}
		delete pStr;
	}
	inFile.close();

	return S_OK;
}

HRESULT RenderManager::IncludeTexture(int stage)
{
	static int c_stage = -1;
	if (stage == c_stage) return S_OK;
	c_stage = stage;

	int len = _msize(m_StageTextureList) / sizeof(TEXTURESET);
	for (int i = 0; len > i; i++)
	{
		m_StageTextureList[i].txt->Release();
	}

	delete m_StageTextureList;
	m_StageTextureList = NULL;
	
	wstring pathq(L"Stage"+to_wstring(stage)+L"/");

	ifstream inFile(pathq + L"Stage"+ to_wstring(stage)+L"Sprite.txt");
	char strasd[200], *tempasd = NULL;
	inFile.getline(strasd, 200);

	int lenq = atoi(strasd);
	m_StageTextureList = new TEXTURESET[lenq];

	for (int i = 0; lenq > i; i++)
	{
		inFile.getline(strasd, 200);
		strtok_s(strasd, " ", &tempasd);

		wchar_t* pStr;
		int strSize = MultiByteToWideChar(CP_ACP, 0, strasd, -1, NULL, NULL);
		pStr = new WCHAR[strSize];
		MultiByteToWideChar(CP_ACP, 0, strasd, strlen(strasd) + 1, pStr, strSize);
		wstring pathtemp(pathq + pStr);

		m_StageTextureList[i].sizex = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].sizey = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].spfx = atoi(strtok_s(NULL, " ", &tempasd));
		m_StageTextureList[i].spfy = atoi(strtok_s(NULL, " ", &tempasd));

		string hex(strtok_s(NULL, " ", &tempasd));
		if (hex[0] == '0'&&'x') { std::stringstream ss(hex); ss >> std::hex >> m_StageTextureList[i].bgc; }
		else {
			int r = atoi(strtok_s(NULL, " ", &tempasd));
			int g = atoi(strtok_s(NULL, " ", &tempasd));
			int b = atoi(strtok_s(NULL, " ", &tempasd));
			m_StageTextureList[i].bgc = D3DCOLOR_XRGB(r, g, b);
		}

		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3DDevice, pathtemp.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001
			, 0x0000001, m_StageTextureList[i].bgc, NULL, NULL, &m_StageTextureList[i].txt)))
		{
			wstring tempc = L"Could not find ";
			tempc += pathtemp;
			MessageBox(NULL, tempc.c_str(), L"Textures.exe", MB_OK);
			return E_FAIL;
		}
		delete pStr;
	}
	inFile.close();

	return S_OK;
}



VOID RenderManager::DrawObj(D3DXVECTOR3 & ipos, int id, RECT & iRect, D3DMATRIX & iMat)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(m_pD3DDevice, &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 ct2(0, 0, 0);
	D3DXMATRIX mat(iMat);
	D3DXMATRIX mat2;
	D3DXMatrixTranslation(&mat2, ipos.x, ipos.y, 0);
	D3DXMatrixMultiply(&mat, &mat, &mat2);
	D3DXMatrixMultiply(&mat, &mat, &m_WorldMat);

	sprite->SetTransform(&mat);
	sprite->Draw(GetTexture(id)->txt, &iRect, NULL, &ct2, D3DXCOLOR(1, 1, 1, 1.0f));
	sprite->End();
	sprite->Release();;
}

VOID RenderManager::DrawParticle(D3DXVECTOR3& ipos, int id, D3DXCOLOR color)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(m_pD3DDevice, &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 ct2(0, 0, 0);
	RECT iRect = { 0,0,GetTexture(id)->sizex,GetTexture(id)->sizey };

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, ipos.x, ipos.y, 0);

	D3DXMatrixMultiply(&mat, &mat, &m_WorldMat);

	sprite->SetTransform(&mat);
	sprite->Draw(GetTexture(id)->txt, &iRect, NULL, &ct2, color);
	sprite->End();
	sprite->Release();
}

VOID RenderManager::DrawParticle(D3DXVECTOR3& ipos, int id, RECT& iRect, D3DXCOLOR color, D3DMATRIX& iMat)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(m_pD3DDevice, &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 ct2(0, 0, 0);

	D3DXMATRIX mat(iMat);
	D3DXMATRIX mat2;
	D3DXMatrixTranslation(&mat2, ipos.x, ipos.y, 0);
	D3DXMatrixMultiply(&mat, &mat, &mat2);
	D3DXMatrixMultiply(&mat, &mat, &m_WorldMat);

	sprite->SetTransform(&mat);
	sprite->Draw(GetTexture(id)->txt, &iRect, NULL, &ct2, color);
	sprite->End();
	sprite->Release();
}

TEXTURESET * RenderManager::GetTexture(int idx)
{ 
	if (idx >= 1000) {
		return &m_GeneralTextureList[idx-1000];
	}
	return &m_StageTextureList[idx];
}

HRESULT RenderManager::BeginScene()
{
	if (NULL == m_pD3DDevice)
		return E_FAIL;

	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	if (FAILED(m_pD3DDevice->BeginScene()))
		return E_FAIL;

	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, 0, 0, 0);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -12.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	if (shaketimer>0)
	{
		D3DXVECTOR2 translation(0, 0);
		translation.x = float ((rand() % shakescale) - (shakescale / 2)) / 1000;
		translation.y = float((rand() % shakescale) - (shakescale / 2)) / 1000;

		D3DXMatrixTransformation2D(&m_WorldMat, NULL, NULL, NULL, NULL, NULL, &translation);
		shaketimer--;
		if (shaketimer == 0) {
			D3DXVECTOR2 translation2(0, 0); D3DXMatrixTransformation2D(&m_WorldMat, NULL, NULL, NULL, NULL, NULL, &translation2);
		}
	}

	D3DXMATRIX mat;
	D3DXMatrixTransformation(&mat, NULL, NULL, NULL, NULL, NULL, NULL);

	int bgid= GET_SYSMANAGER()->GetCurrentBGID();
	if (bgid != -1) {
		RECT rtemp = { 0,0,m_StageTextureList[bgid].spfx,m_StageTextureList[bgid].spfy };
		DrawObj(D3DXVECTOR3(0, (MAX_Y-20- m_StageTextureList[bgid].spfy)/2, 0), bgid, rtemp, mat);
	}

	return S_OK;
}




VOID RenderManager::ResetDefaultMatrix()
{
	D3DXMatrixTranslation(&m_WorldMat,NULL,NULL,0.0);
}




VOID RenderManager::SetDefaultMatrixZoomUp(D3DXVECTOR2& Center,float scale)
{
	D3DXVECTOR2 ct = Center;
	D3DXVECTOR2 ct2 =  D3DXVECTOR2(MAX_X / 2, MAX_Y / 2)-Center;

	D3DXVECTOR2 scaling(scale, scale);

	D3DXMatrixTransformation2D(&m_WorldMat,&ct , 0.0, &scaling, NULL, NULL, &ct2);
}

VOID RenderManager::SetDefaultMatrixShake(int scale,int maxframe)
{
	shaketimer = maxframe;
	shakescale = scale;
}

HRESULT RenderManager::EndScene()
{
	if (GET_SYSMANAGER()->IsBossRoom()) {
		D3DXMATRIX mat;
		D3DXMatrixTransformation(&mat, NULL, NULL, NULL, NULL, NULL, NULL);
		RECT rtemp2 = { 0,0,640,480 };
		DrawObj(D3DXVECTOR3(0, 0, 0), TXTID_BR_FADE, rtemp2, mat);
	}

	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

