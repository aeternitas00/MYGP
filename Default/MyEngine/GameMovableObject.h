#pragma once
#include "GameObject.h"
class GameMovableObject :
	public GameObject
{
public:
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
protected:
	PhysicsComponent* pPhsComponent;
public:
	GameMovableObject();
	GameMovableObject(D3DXVECTOR3& ipos, D3DXVECTOR3& ivel, D3DXVECTOR3& iacc, int id);
	virtual ~GameMovableObject();
	virtual VOID update();
};

