#pragma once
#include "stdafx.h"


class PhysicsComponent:public ComponentBase
{
protected:
	FRECT volume;
public:
	PhysicsComponent();

	bool CollisionCheck(const FRECT one, const FRECT two);
	bool CollisionCheck(D3DXVECTOR3 & pone, D3DXVECTOR3 & ptwo, static std::list<FRECT>& vlone, static std::list<FRECT>& vltwo);
	virtual VOID Update(GameObject* pObj);
	virtual ~PhysicsComponent();
};

