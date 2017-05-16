#pragma once

#include "stdafx.h"
#include <list>
#define TXTID_BG 0
#define TXTID_EXPLODE_SMALL 1
#define TXTID_PLAYER_BULLET 2
#define TXTID_PLAYER 3
#define TXTID_DUST 4
#define TXTID_BLOCK_CM 5
using namespace std;

typedef struct __txtset {
	wstring path;
	int sizex, sizey, spfx, spfy;
	D3DCOLOR bgc;
	LPDIRECT3DTEXTURE9 txt;
}TEXTURESET;

typedef struct __risqr
{
	int x, y;
}RENDERSQUARE;

class RenderManager
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPD3DXSPRITE		m_pD3DSprite;
	
	TEXTURESET*			m_TextureList;
	static RenderManager*	instance;
	
	RenderManager();
	HRESULT				Initialize();
	HRESULT				IncludeTexture();
public :
	~RenderManager();

	static RenderManager*	GetInstance();
	

	LPDIRECT3DDEVICE9*	GetDevice(){return &m_pD3DDevice;}
	LPD3DXSPRITE*		GetSprite(){return &m_pD3DSprite;}
	TEXTURESET*			GetTexture(int idx) { return &m_TextureList[idx]; }
	TEXTURESET*			GetTexture(const wchar_t* path);
	HRESULT				BeginScene();
	VOID SetupDefaultMatrix();
	HRESULT				EndScene();
};
