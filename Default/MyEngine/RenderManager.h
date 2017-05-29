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
#define	TXTID_SAVEPOINT 12
#define TXTID_TITLE 0
#define TXTID_INTROBLK1 1
#define TXTID_INTROBLK2 2
#define TXTID_INTROKID 3
#define TXTID_INTROBOSHY 4
#define TXTID_INTROBLK3 5
#define TXTID_INTROBLK4 6
#define TXTID_INTROKID2 7
using namespace std;

typedef struct __txtsettemp {
	wstring path;
	int sizex, sizey, spfx, spfy;
	D3DCOLOR bgc;
	LPDIRECT3DTEXTURE9 txt;
}TEXTURESETTEMP;

typedef struct __txtset {
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
	D3DXMATRIX			m_WorldMat;
	TEXTURESET*			m_TextureList;
	static RenderManager*	instance;
	
	RenderManager();
	HRESULT				Initialize();
	HRESULT				IncludeTexture();
	
public :
	~RenderManager();

	static RenderManager*	GetInstance();
	
	HRESULT				IncludeTexture(int stage);
	LPDIRECT3DDEVICE9*	GetDevice(){return &m_pD3DDevice;}
	D3DXMATRIX*	GetWorldMatrix() { return &m_WorldMat; }
	VOID DrawObj(D3DXVECTOR3& ipos, int id, RECT& iRect, D3DMATRIX& iMat);
	VOID DrawParticle(D3DXVECTOR3 & ipos, int id, D3DXCOLOR color);
	TEXTURESET*			GetTexture(int idx) { return &m_TextureList[idx]; }
	TEXTURESET*			GetTexture(const wchar_t* path);
	HRESULT				BeginScene();
	VOID ResetDefaultMatrix();
	VOID SetDefaultMatrixZoomUp(D3DXVECTOR2 & Center, float scale);
	HRESULT				EndScene();
};
