#pragma once

#include "stdafx.h"
#include <list>
#define TXTID_BG 0
#define TXTID_EXPLODE_SMALL 1
#define TXTID_PLAYER_BULLET 2
#define TXTID_PLAYER 3
#define TXTID_DUST 4
#define TXTID_BLOCK_CM 5
#define TXTID_BLOCK_CM2 6
#define TXTID_MISSILE_LBARREL 7
#define TXTID_MISSILE_LBASE 8
#define TXTID_SPIKE 9
#define TXTID_PARTICLE_2X2 10
#define TXTID_PARTICLE_4X4 11
#define TXTID_SAVEPOINT 12
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
	D3DXMATRIX			m_WorldMat;
	TEXTURESET*			m_TextureList;
	static RenderManager*	instance;
	
	RenderManager();
	HRESULT				Initialize();
	HRESULT				IncludeTexture();
public :
	~RenderManager();

	static RenderManager*	GetInstance();
	

	LPDIRECT3DDEVICE9*	GetDevice(){return &m_pD3DDevice;}
	LPD3DXSPRITE*			GetSprite(){return &m_pD3DSprite;}
	VOID							DrawObj(D3DXVECTOR3&, int , RECT& , D3DMATRIX& );
	VOID							DrawParticle(D3DXVECTOR3 & , int , D3DXCOLOR );
	TEXTURESET*				GetTexture(int idx) { return &m_TextureList[idx]; }
	TEXTURESET*				GetTexture(const wchar_t*);
	HRESULT						BeginScene();
	VOID							SetupDefaultMatrix();
	VOID							SetZoomUpMatrix(D3DXVECTOR2 &, float);
	HRESULT						EndScene();
};
