#pragma once
#include "ComponentBase.h"
class ObjectShake :
	public ComponentBase
{
private:
	float m_time;
	int m_power;
	int m_acc;
	D3DXVECTOR3 m_pos;
	clock_t after, before;
	bool gook;
private:
	ObjectShake();
public:
	ObjectShake(float time,int power,int acc,D3DXVECTOR3& pos);
	~ObjectShake();
	virtual RESULT Update(GameObject* pObj);
};

