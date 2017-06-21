#pragma once
#include "ComponentBase.h"
class BulletGenerate1 :
	public ComponentBase
{
private:
	EnemyBullet samplebullet;
	int m_time;
	int delay;
	int frame;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_vector;
	bool gook;
private:
	BulletGenerate1();
public:
	BulletGenerate1(int time,int delay, D3DXVECTOR3& vector, D3DXVECTOR3&,EnemyBullet&);
	virtual RESULT Update(GameObject* pObj);
	~BulletGenerate1();
};

