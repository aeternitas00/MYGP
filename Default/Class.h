#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <Winuser.h>

#define ACC_GRV 0.96f
#define MIN_Y 290
#define MIN_X 200
#define MAX_X 505
#define MAX_Y 515
#define MAX_BULLET 5
#define EXPLODE_1_FRM 7
#define OBJ_DESTROY 1
#define OBJ_DEFAULT 0
#define OBJ_MAKE_EXPL 2
#define OBJ_BUL_HIT_BLOCK 3

class CParent
{
protected:
	D3DXVECTOR3 mpos; // The position
	LPDIRECT3DTEXTURE9 pTexture;
	RECT rctperfrm;
	UINT txtwidth;
	UINT txtheight;
	int mfrm;
	int nfrm;
public:
	CParent() {}
	CParent(D3DXVECTOR3* ipPos, LPDIRECT3DTEXTURE9 ipTxt, const int imfrm, const RECT iRct);	
	virtual short draw(LPD3DXSPRITE* ipSprt);
	inline D3DXVECTOR3 getpos() { return mpos; }
};

class CChild : public CParent
{
private:
	float vel;
public:
	CChild() {}
	CChild(D3DXVECTOR3* ipPos, LPDIRECT3DTEXTURE9 ipTxt, const int imfrm, const RECT iRct, float ivel);
	virtual short draw(LPD3DXSPRITE* ipSprt);
	bool move();
};