#pragma once
#include "stdafx.h"


class GameObject
{
protected:
	D3DXVECTOR3 m_pos;
	LPDIRECT3DTEXTURE9 m_txt;

public:
	GameObject();
	HRESULT SetTxt() { return S_OK; }
	virtual ~GameObject();
};

