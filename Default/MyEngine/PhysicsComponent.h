#pragma once
#include "stdafx.h"

typedef std::list<D3DXVECTOR2> MyPolygon;

class PhysicsComponent:public ComponentBase
{
protected:
	/*FRECT volume;*/
public:
	PhysicsComponent();

	bool ComparePolygon(MyPolygon & , MyPolygon & , D3DXVECTOR2 & , D3DXVECTOR2 & , float , float );

	D3DXVECTOR2 RotatenMove(D3DXVECTOR2& ivec, float angle, D3DXVECTOR2& center);
	float GetMaxY(MyPolygon & , float , D3DXVECTOR2 & , D3DXVECTOR2 & );
	float GetMinY(MyPolygon &, float, D3DXVECTOR2 &, D3DXVECTOR2 &);
	bool CollisionCheck(const FRECT one, const FRECT two);
	bool CollisionCheck(D3DXVECTOR3 & pone, D3DXVECTOR3 & ptwo, static std::list<FRECT>& vlone, static std::list<FRECT>& vltwo);
	virtual RESULT Update(GameObject* pObj);
	bool CollisionDetection(GameObject * ObjA, GameObject * ObjB);
	virtual ~PhysicsComponent();
};

