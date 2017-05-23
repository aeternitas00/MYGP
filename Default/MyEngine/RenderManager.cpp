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
	if (m_pD3DSprite != NULL)
		m_pD3DSprite->Release();

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
		{L"Sprite_BG.jpg",640,360,640,360,0xFFFFFFFF,},
		{L"Sprite_ExplodeSmall.png",256,32,32,32,D3DCOLOR_XRGB(50, 150, 200), },
		{L"Sprite_PlayerBullet.png",8,7,8,7,0xFFFFFFFF, },
		{L"Sprite_Player.png",440,66,40,33,0xFFFFFFFF, },
		{L"Sprite_FXDust.png",720,80,120,20,D3DCOLOR_XRGB(4,142,176), },
		{L"Sprite_Block_CM.png",16,16,16,16,D3DCOLOR_XRGB(4,142,176), },
		{ L"Sprite_Block_CM2.png",16,16,16,16,0xFFFFFFFF, },
		{ L"Sprite_Block_MLauncher.png",16,16,16,16,0xFFFFFFFF, },
		{ L"Sprite_Block_MLBase.png",16,16,16,16,0xFFFFFFFF, },
		{L"Sprite_SpikeM.png",128,32,32,32,0xFFFFFFFF,},
		{ L"Sprite_Blank_2x2.png",2,2,2,2,0x00000000, },
		{ L"Sprite_Blank_4x4.png",7,6,7,6,D3DCOLOR_XRGB(0,0,0), },
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

VOID RenderManager::DrawObj(D3DXVECTOR3& ipos,int id,RECT& iRect, D3DMATRIX& iMat)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(m_pD3DDevice, &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 ct(ipos); D3DXVECTOR3 ct2(0, 0, 0);
	D3DXMATRIX mat(iMat);

	D3DXMatrixMultiply(&mat, &mat, &m_WorldMat);

	sprite->SetTransform(&mat);
	sprite->Draw(GetTexture(id)->txt, &iRect, NULL, &ct2, D3DXCOLOR(1, 1, 1, 1.0f));
	sprite->End();
	sprite->Release();
}
VOID RenderManager::DrawParticle(D3DXVECTOR3& ipos, int id, D3DXCOLOR color)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(m_pD3DDevice, &sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 ct(ipos); D3DXVECTOR3 ct2(0, 0, 0);
	RECT iRect = { 0,0,GetTexture(id)->sizex,GetTexture(id)->sizey };

	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, ipos.x, ipos.y, 0);

	D3DXMatrixMultiply(&mat, &mat, &m_WorldMat);

	sprite->SetTransform(&mat);
	sprite->Draw(GetTexture(id)->txt, &iRect, NULL, &ct2, color);
	sprite->End();
	sprite->Release();
}
TEXTURESET * RenderManager::GetTexture(const wchar_t * path)
{
	// do hashing;
	return nullptr;
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


	if (FAILED(m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND)))

		return E_FAIL;
	SetupDefaultMatrix();



	int bgid= SystemManager::GetInstance()->GetCurrentBGID();
	RECT rtemp = { 0,0,m_TextureList[bgid].spfx,m_TextureList[bgid].spfy };
	DrawObj(D3DXVECTOR3(0, 40, 0), bgid, rtemp, m_WorldMat);

	return S_OK;
}

VOID RenderManager::SetupDefaultMatrix()
{
	//D3DXVECTOR2 spriteCentre = D3DXVECTOR2(MAX_X / 2, MAX_Y);
	//D3DXVECTOR2 trans(0, 0);

	//D3DXMatrixTransformation2D(&m_WorldMat, NULL, NULL, NULL, NULL, NULL, NULL);
	D3DXMatrixTranslation(&m_WorldMat,NULL,NULL,0.0);
	m_pD3DSprite->SetTransform(&m_WorldMat);
}
VOID RenderManager::SetZoomUpMatrix(D3DXVECTOR2& Center,float scale)
{
	D3DXVECTOR2 ct = Center;
	D3DXVECTOR2 ct2 =  D3DXVECTOR2(MAX_X / 2, MAX_Y / 2)-Center;
	// Screen position of the sprite
	//D3DXVECTOR2 trans = D3DXVECTOR2(50.0f, 80.0f);

	//// Rotate based on the time passed
	//float rotation = timeGetTime() / 500.0f;

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	D3DXVECTOR2 scaling(scale, scale);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat,&ct , 0.0, &scaling, NULL, NULL, &ct2);

	// Tell the sprite about the matrix
	m_pD3DSprite->SetTransform(&mat);
}
HRESULT RenderManager::EndScene()
{
	m_pD3DSprite->End();
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}

