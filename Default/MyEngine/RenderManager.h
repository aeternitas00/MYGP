#pragma once

#include "stdafx.h"
#include <queue>
using namespace std;

class RenderManager
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPD3DXSPRITE		m_pD3DSprite;
	
	static RenderManager* instance;

	RenderManager();
	HRESULT Initialize();
	HRESULT m_Add_Txt();
public :
	~RenderManager();

	static RenderManager* GetInstance();

	LPDIRECT3DDEVICE9*	GetDevice(){return &m_pD3DDevice;}
	LPD3DXSPRITE*		GetSprite(){return &m_pD3DSprite;}
	HRESULT				BeginScene();
	HRESULT				EndScene();
};
