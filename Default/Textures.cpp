//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. Textures can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. Textures are
//       typically loaded from image files, and D3DX provides a utility to
//       function to do this for us. Like a vertex buffer, Textures have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" Textures, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D texture coordinate generation (which is an advanced feature).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include "Class.h"
#include <list>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture = NULL; // Our texture
LPDIRECT3DTEXTURE9      g_pTexturebg = NULL; // Our texture
LPDIRECT3DTEXTURE9      g_pTextureDust = NULL; // Our texture
LPDIRECT3DTEXTURE9		g_pTextureExplode = NULL;
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;
LPDIRECT3DTEXTURE9		g_pTextureBlock = NULL;
LPDIRECT3DTEXTURE9		g_pTextureCrack0 = NULL;
LPDIRECT3DTEXTURE9		g_pTextureCrack1 = NULL;
LPDIRECT3DTEXTURE9		g_pTextureCrack2 = NULL;
LPDIRECT3DTEXTURE9		g_pTextureCrack3 = NULL;
LPD3DXSPRITE	g_pd3dSprite = NULL;
D3DXIMAGE_INFO g_Imgtemp;
RECT g_ImgRc1;
RECT g_ImgRcbg;
RECT g_ImgRcDust;

D3DXVECTOR3 pos(225, MIN_Y, 0);
D3DXVECTOR3 dustpos(0, 0, 0);


// A structure for our custom vertex type. We added texture coordinates
enum DIR {
	LEFT=-1,
	RIGHT=1
};
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DCOLOR color;    // The color
    FLOAT tu, tv;   // The texture coordinates
};


// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
CUSTOMVERTEX* pVertices2;


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	 
	


    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn off culling
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Create the Textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{	
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"bg.bmp", &g_pTexturebg)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\bg.bmp", &g_pTexturebg)))
		{
			MessageBox(NULL, L"Could not find bg.bmp", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"crack0.png", &g_pTextureCrack0)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\crack0.png", &g_pTextureCrack0)))
		{
			MessageBox(NULL, L"Could not find crack0.png", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"crack1.png", &g_pTextureCrack1)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\crack1.png", &g_pTextureCrack1)))
		{
			MessageBox(NULL, L"Could not find crack1.png", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"crack2.png", &g_pTextureCrack2)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\crack2.png", &g_pTextureCrack2)))
		{
			MessageBox(NULL, L"Could not find crack2.png", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"crack3.png", &g_pTextureCrack3)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\crack3.png", &g_pTextureCrack3)))
		{
			MessageBox(NULL, L"Could not find crack3.png", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"block.png", &g_pTextureBlock)))
	{
		// If texture is not in current folder, try parent folder
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\block.png", &g_pTextureBlock)))
		{
			MessageBox(NULL, L"Could not find block.png", L"Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pd3dSprite)))
	{
		g_pd3dDevice->Release();
		g_pd3dDevice = NULL;

		g_pD3D->Release();
		g_pD3D = NULL;

		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice, L"bmp12313.png", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED	,
		0x0000001	, 0x0000001	, 0xFFFFFFFF	, &g_Imgtemp, NULL, &g_pTexture))) {
		MessageBox(NULL, L"Could not find bmp12313.png", L"Textures.exe", MB_OK);
		return E_FAIL;
	}::SetRect(&g_ImgRc1, 0, 0, g_Imgtemp.Width, g_Imgtemp.Height);


	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice	, L"bg.bmp"	, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		0x0000001	, 0x0000001	, 0xFFFFFFFF, &g_Imgtemp, NULL, &g_pTexturebg))) {
		MessageBox(NULL, L"Could not find bg.bmp", L"Textures.exe", MB_OK);
		return E_FAIL;
	}::SetRect(&g_ImgRcbg, 0, 0, g_Imgtemp.Width, g_Imgtemp.Height);

	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice, L"bullet.png", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		0x0000001, 0x0000001, 0xFFFFFFFF, &g_Imgtemp, NULL, &g_pTextureBullet))) {
		MessageBox(NULL, L"Could not find bullet.png", L"Textures.exe", MB_OK);
		return E_FAIL;
	}


	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice				// 디바이스 포인터
		, L"Sprite_FX_Dust.png"
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1							// 밉 레벨(2D의 경우 반드시 1)
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x0000001					// 필터링
		, 0x0000001					// 밉 필터
		, D3DCOLOR_XRGB(4,142,176)				// 컬러 키
		, &g_Imgtemp					// 텍스처 인포메이션
		, NULL
		, &g_pTextureDust					// 텍스처 포인터
		))) {
		MessageBox(NULL, L"Could not find Sprite_FX_Dust.png", L"Textures.exe", MB_OK);
		return E_FAIL;
	}::SetRect(&g_ImgRcDust, 0, 0, g_Imgtemp.Width, g_Imgtemp.Height);

	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice, L"explodesmall.png", D3DX_DEFAULT, D3DX_DEFAULT, 1	, 0	, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
		0x0000001, 0x0000001, D3DCOLOR_XRGB(50, 150, 200), &g_Imgtemp,NULL,&g_pTextureExplode))) {
		MessageBox(NULL, L"Could not find explodesmall.png", L"Textures.exe", MB_OK);
		return E_FAIL;
	}

    // Create the vertex buffer.
	CUSTOMVERTEX vertecies[] = {
		{ D3DXVECTOR3(3.0f, -1.3f, 0.f), D3DCOLOR(0xffffffff), 0.f, 0.f },
		{ D3DXVECTOR3(4.0f, -1.3f, 0.f), D3DCOLOR(0xffffffff), 1.f, 0.f },
		{ D3DXVECTOR3(3.0f, -2.3f, 0.f), D3DCOLOR(0xffffffff), 0.f, 1.f },

		{ D3DXVECTOR3(4.0f, -1.3f, 0.f), D3DCOLOR(0xffffffff), 1.f, 0.f },
		{ D3DXVECTOR3(3.0f, -2.3f, 0.f), D3DCOLOR(0xffffffff), 0.f, 1.f },
		{ D3DXVECTOR3(4.0f, -2.3f, 0.f), D3DCOLOR(0xffffffff), 1.f, 1.f },
	};

	// 정점 버퍼 생성
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(vertecies), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL))) {
		return E_FAIL;
	}

	CUSTOMVERTEX* pVertices;

	// Lock() 함수의 첫 번째와 두 번째 인자를 0으로 전달하면
	// Vertex Buffer의 전체 버퍼 크기로 설정
	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0))) {
		return E_FAIL;
	}
	memcpy(pVertices, &vertecies, sizeof(vertecies));

	g_pVB->Unlock();
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{

	if (g_pd3dSprite)
		g_pd3dSprite->Release();

    if( g_pTexture != NULL )
        g_pTexture->Release();

    if( g_pVB != NULL )
        g_pVB->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
	// Set up world matrix
	


	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, 0, 0, 0);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -12.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);


	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

VOID SetupMatrices2()
{

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, 0, 0, 0);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -12.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);


	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);



	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		static bool go_left;
		static bool go_right = true;
		static bool moving;
		static short stat = 0;
		static bool increase = true;

		static float upvel = 0;
		static bool jumping_up = false;
		static bool jumping = false;
		static bool jumping_tgl = false;

		static float sliding_vel = 0;
		static short sliding = 0;
		static short sliding_rt = 0;
		static bool sliding_tgl = false;

		static bool attack = false;
		static bool attack_tgl = false;
		static int attack_rmt = 0;

		static std::list<CParent*> MyList;

		static int blockHP = 0;

		moving = false;

		SetupMatrices();

		if (sliding == 0)
		{
			if (KEY_DOWN(VK_LEFT)) {
				go_left = true; go_right = false; moving = true;
			}
			if (KEY_DOWN(VK_RIGHT)) {
				go_right = true; go_left = false; moving = true;
			}
			if (KEY_DOWN(VK_UP)) {
				if (!jumping&&!jumping_tgl) {
					jumping_tgl = true;
					jumping = true; jumping_up = true; upvel = 6.0f;
				}
				else if (jumping) {
					if (jumping_up)
						upvel += 0.495;
				}
			}
			if (jumping_tgl) { if (KEY_UP(VK_UP)) jumping_tgl = false; }

			if (KEY_DOWN(0x58/*x Key*/)) {
				if (!attack_tgl) {
					attack = true;	attack_tgl = true;
					D3DXVECTOR3 temp(pos);
					if (go_right) {
						temp.x += 50; temp.y += 32;
						MyList.push_back(new CChild(&temp, g_pTextureBullet, 1, RECT{ 0,0,8,7 }, 4.0f));
						attack_rmt = 8;
					}
					else if (go_left) {
						temp.x -= 11; temp.y += 32;
						MyList.push_back(new CChild(&temp, g_pTextureBullet, 1, RECT{ 0,0,8,7 }, -4.0f));
						attack_rmt = 18;
					}
				}
			}
			if (attack_tgl) { if (KEY_UP(0x58)) attack_tgl = false; }

			if (KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_RIGHT) || KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_LEFT)) {
				if (!sliding_tgl&&!jumping) {
					sliding_tgl = true; attack = false; attack_rmt = 0;
					dustpos = pos; dustpos.y += 43;
					if (go_left)dustpos.x -= 60;

					sliding_rt = 15;
					moving = false;
					sliding_vel = 8;
					if (go_right) sliding = 1;/*right*/
					else if (go_left)  sliding = 2;/*left*/
				}
			}
			if (sliding_tgl) { if (KEY_UP(VK_DOWN)) sliding_tgl = false; }
		}

		if (go_left&&go_right)
			moving = false;

		if (!moving&&!jumping&&sliding == 0)
		{
			if (go_right) {
				g_ImgRc1.left = 0;
				g_ImgRc1.right = g_ImgRc1.left + 66;
			}
			else if (go_left) {
				g_ImgRc1.left = 462;
				g_ImgRc1.right = g_ImgRc1.left + 66;
			}
			else if (!go_right&&!go_left)
			{
				g_ImgRc1.left = 0;
				g_ImgRc1.right = g_ImgRc1.left + 66;
			}
			if (!attack) {
				g_ImgRc1.top = 0;
				g_ImgRc1.bottom = 65;
			}
			else {
				g_ImgRc1.top = 66;
				g_ImgRc1.bottom = 131;
			}
		}
		else if (moving&&!jumping)
		{
			if (!attack) {
				g_ImgRc1.top = 0;
				g_ImgRc1.bottom = 65;
			}
			else {
				g_ImgRc1.top = 66;
				g_ImgRc1.bottom = 131;
			}
			if (go_right)
			{
				if (stat >= 0 && stat <= 7) {
					g_ImgRc1.left = 66;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
				else if (stat >= 8 && stat <= 23) {
					g_ImgRc1.left = 132;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
				else if (stat >= 24 && stat <= 31) {
					g_ImgRc1.left = 198;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
			}
			else if (go_left)
			{
				if (stat >= 0 && stat <= 7) {
					g_ImgRc1.left = 396;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
				else if (stat >= 8 && stat <= 23) {
					g_ImgRc1.left = 330;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
				else if (stat >= 24 && stat <= 31) {
					g_ImgRc1.left = 264;
					g_ImgRc1.right = g_ImgRc1.left + 65;
				}
			}

		}
		else if (jumping) {
			if (!attack) {
				g_ImgRc1.top = 0;
				g_ImgRc1.bottom = 65;
			}
			else {
				g_ImgRc1.top = 66;
				g_ImgRc1.bottom = 131;
			}
			if (go_right) {
				g_ImgRc1.left = 528;
				g_ImgRc1.right = g_ImgRc1.left + 65;
			}
			else if (go_left) {
				g_ImgRc1.left = 594;
				g_ImgRc1.right = g_ImgRc1.left + 65;
			}
		}

		else if (sliding) {
			g_ImgRc1.top = 0;
			g_ImgRc1.bottom = 65;
			if (go_right) {
				g_ImgRc1.left = 660;
				g_ImgRc1.right = g_ImgRc1.left + 59;
			}
			else if (go_left) {
				g_ImgRc1.left = 720;
				g_ImgRc1.right = g_ImgRc1.left + 59;
			}
		}
		if (stat >= 31) increase = false; else if (stat <= 0)increase = true;
		if (increase)stat++; else stat--;
		if (moving)
		{
			if (go_left) pos.x -= 2.0f; if (go_right) pos.x += 2.0f;
		}
		if (attack)
		{
			if (attack_rmt <= 0)attack = false;
			attack_rmt--;
		}
		else if (sliding != 0)
		{
			if (go_left) pos.x -= sliding_vel; if (go_right) pos.x += sliding_vel;
			sliding_vel -= 0.45f;
			if (sliding_rt >= 4) {
				if (go_right) {
					g_ImgRcDust.left = ((15 - sliding_rt) * 120) % 720;
					g_ImgRcDust.right = g_ImgRcDust.left + 119;
					if (9 >= sliding_rt)g_ImgRcDust.top = 20;
					else g_ImgRcDust.top = 0;
					g_ImgRcDust.bottom = g_ImgRcDust.top + 19;
				}
				else if (go_left) {
					g_ImgRcDust.right = 720 - ((15 - sliding_rt) * 120) % 720;
					g_ImgRcDust.left = g_ImgRcDust.right - 119;
					if (9 >= sliding_rt)g_ImgRcDust.top = 60;
					else g_ImgRcDust.top = 40;
					g_ImgRcDust.bottom = g_ImgRcDust.top + 19;
				}

			}
			sliding_rt--; if (sliding_rt == -1) sliding = 0;
		}
		if (jumping)
		{
			if (upvel <= 0) jumping_up = false;
			if (pos.y - upvel >= MIN_Y) { pos.y = MIN_Y; jumping = false; /*먼지 스프라이트 추가*/ }
			else { pos.y -= upvel; upvel -= ACC_GRV; }
		}

		// Setup the world, view, and projection matrices
		g_pd3dDevice->SetTexture(0, g_pTextureBlock);

		if (blockHP >= 500)
			g_pd3dDevice->SetTexture(1, g_pTextureCrack3);
		else if (blockHP >= 250)
			g_pd3dDevice->SetTexture(1, g_pTextureCrack2);
		else if (blockHP >= 100)
			g_pd3dDevice->SetTexture(1, g_pTextureCrack1);
		else if (blockHP >= 0)
			g_pd3dDevice->SetTexture(1, g_pTextureCrack0);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		g_pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		g_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		g_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
		g_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		g_pd3dDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
		g_pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		g_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

		//RECT blocktemp = { 0,0,61,61 };
		g_pd3dSprite->Draw(g_pTexturebg, &g_ImgRcbg, NULL, &D3DXVECTOR3(0, 0, 1), D3DXCOLOR(1, 1, 1, 1.0f));
		D3DXVECTOR3 postemp(pos);
		if (go_left)postemp.x -= 16;
		g_pd3dSprite->Draw(g_pTexture, &g_ImgRc1, &D3DXVECTOR3(0, 0, 0), &postemp, D3DXCOLOR(1, 1, 1, 1.0f)); // center is NULL
		//g_pd3dSprite->Draw(g_pTextureBlock, &blocktemp, NULL, &D3DXVECTOR3(100,100, 0), D3DXCOLOR(1, 1, 1, 1.0f));
		D3DXVECTOR3 tempos;
		for (auto n = MyList.begin(); n != MyList.end();)
		{
			switch ((*n)->draw(&g_pd3dSprite)) {
			case OBJ_DEFAULT:
				n++;
				break;
			case OBJ_DESTROY:
				delete *n; MyList.erase(n++);
				break;
			case OBJ_MAKE_EXPL:
				tempos = (*n)->getpos();
				tempos.x -= 11.0; tempos.y -= 12.5;
				MyList.push_back(new CParent(&tempos, g_pTextureExplode, EXPLODE_1_FRM, RECT{ 0,0,32,32 }));
				delete *n; MyList.erase(n++);
				break;
			case OBJ_BUL_HIT_BLOCK:
				tempos = (*n)->getpos();
				tempos.x -= 11.0; tempos.y -= 12.5;
				MyList.push_back(new CParent(&tempos, g_pTextureExplode, EXPLODE_1_FRM, RECT{ 0,0,32,32 }));
				delete *n; MyList.erase(n++); blockHP += 35;
				break;
			}

		}
		if (sliding) {
			g_pd3dSprite->Draw(g_pTextureDust, &g_ImgRcDust, NULL, &dustpos, D3DXCOLOR(1, 1, 1, float((sliding_rt + 1) / 15.0f)));
		}
		// End the scene
		if(blockHP>=1)blockHP--;
		g_pd3dSprite->End();
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));

		// D3D에 정점 정보를 제공한다.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// 실제 기하 물체를 그린다.
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 05: Textures",
                              WS_OVERLAPPEDWINDOW, 200, 200, 525, 515,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the scene geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
				else {
					Render();
				}
            }
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



