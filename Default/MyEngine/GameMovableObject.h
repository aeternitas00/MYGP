#pragma once
#include "GameObject.h"
class GameMovableObject :
	public GameObject
{
public:
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
protected:

public:
	virtual VOID SetComponent();
	virtual RESULT Update();
	GameMovableObject();
	GameMovableObject(D3DXVECTOR3& ipos, D3DXVECTOR3& ivel, D3DXVECTOR3& iacc, int id);
	~GameMovableObject();
};

