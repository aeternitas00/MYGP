#include "stdafx.h"
#include "BulletGenerate1.h"


BulletGenerate1::BulletGenerate1(int time, int idelay,D3DXVECTOR3& ivector,D3DXVECTOR3& start, EnemyBullet& sample)
	:m_time(time),m_vector(ivector),gook(true),delay(idelay),samplebullet(sample),m_pos(start),sndid(-1)
{
	frame = 0;
}

BulletGenerate1::BulletGenerate1(int time, int idelay, D3DXVECTOR3 & ivector, D3DXVECTOR3& start, EnemyBullet& sample, int isndid)
	: m_time(time), m_vector(ivector), gook(true), delay(idelay), samplebullet(sample), m_pos(start),sndid(isndid)
{
	frame = 0;
}

RESULT BulletGenerate1::Update(GameObject * pObj)
{
	if (gook) {
		frame++;
		if (frame == delay) {
			EnemyBullet* input = new EnemyBullet(samplebullet);
			input->velocity = m_vector;
			GET_SYSMANAGER()->AddEnemyBullet(input);
			if (sndid != -1)
				GET_SNDMANAGER()->PlayWaveFile(sndid);
			frame = 0;
			if (m_time > 0){
				m_time--;
				if (m_time == 0)
				{
					gook = false; return Destroy;
				}
			}
		}
	}
	return Default;
}

BulletGenerate1::BulletGenerate1()
{
}


BulletGenerate1::~BulletGenerate1()
{
}
