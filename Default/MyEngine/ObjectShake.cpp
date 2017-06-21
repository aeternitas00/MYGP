#include "stdafx.h"
#include "ObjectShake.h"


ObjectShake::ObjectShake()
{
}


ObjectShake::ObjectShake(float itime, int power, int acc, D3DXVECTOR3& pos)
	:m_time(itime),m_pos(pos),m_power(power),m_acc(acc),gook(true)
{
	before = clock();
}

ObjectShake::~ObjectShake()
{
}

RESULT ObjectShake::Update(GameObject * pObj)
{
	if (gook) {
		after = clock();
		pObj->pos.x = m_pos.x + ((rand() % m_power) - (m_power / 2)) / 1000;
		pObj->pos.y = m_pos.y + ((rand() % m_power) - (m_power / 2)) / 1000;
		m_power -= m_acc;
		if (!((double)(after - before) / CLOCKS_PER_SEC <= m_time && m_power >= 0))
		{
			gook = false; pObj->pos = m_pos; return Destroy;
		}
	}
	return Default;
}
