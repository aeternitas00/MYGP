#pragma once

#include "stdafx.h"
#include <queue>
using namespace std;

class RenderManager
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;

	queue<LPDIRECT3DTEXTURE9>	m_Txt_list;
	
	static RenderManager* instance;

	RenderManager();
	HRESULT Initialize();
	HRESULT m_Add_Txt();
public :
	~RenderManager();

	
	static RenderManager* GetInstance();
	

	VOID Render();
};
