#pragma once
#include "stdafx.h"
#include <list>
using namespace std;
class ComponentBase;
class GameObject
{
protected:
	D3DXVECTOR3 m_pos;
	LPDIRECT3DTEXTURE9 m_txt;
	std::list<ComponentBase*> ComponentList;
public:
	GameObject();
	HRESULT SetTxt() { return S_OK; }
	virtual ~GameObject();
	VOID update() {
		return;
	}
};

