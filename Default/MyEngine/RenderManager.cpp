#include "stdafx.h"

RenderManager* RenderManager::instance = NULL;

RenderManager::RenderManager()
{
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

	delete m_TextureList;
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
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	if (FAILED(IncludeTexture()))return E_FAIL;

	return S_OK;
}

HRESULT RenderManager::IncludeTexture()
{
	TEXTURESET temp[]={
		{L"Sprite_BG.bmp",512,480,512,480,0xFFFFFFFF,NULL},
		{L"Sprite_ExplodeSmall.png",256,32,32,32,D3DCOLOR_XRGB(50, 150, 200),NULL },
		{L"Sprite_PlayerBullet.png",8,7,8,7,0xFFFFFFFF,NULL },
		{L"Sprite_Player.png",780,132,65,66,0xFFFFFFFF,NULL },
		{L"Sprite_FXDust.png",720,80,120,20,D3DCOLOR_XRGB(4,142,176),NULL },
	};

	int len = sizeof(temp) / sizeof(TEXTURESET);
	for (auto& it : temp)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			m_pD3DDevice, it.path.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001
			, 0x0000001, it.bgc	, NULL, NULL, &it.txt))) 
		{
			wstring tempc = L"Could not find ";
			tempc += it.path;
			MessageBox(NULL, tempc.c_str(), L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}

	m_TextureList = new TEXTURESET[len];
	memcpy(m_TextureList, temp, len*sizeof(TEXTURESET));
	// do hashing
	return S_OK;
}

TEXTURESET * RenderManager::GetTexture(const char * path)
{
	// do hashing;
	return nullptr;
}

HRESULT RenderManager::BeginScene()
{
	if (NULL == m_pD3DDevice)
		return E_FAIL;

	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	
	if (FAILED(m_pD3DDevice->BeginScene()))
		return E_FAIL;
	if (FAILED(m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND)))
		return E_FAIL;

	return S_OK;
}

HRESULT RenderManager::EndScene()
{
	m_pD3DSprite->End();
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}
