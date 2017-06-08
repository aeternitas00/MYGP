#include "stdafx.h"
#include "SavePoint.h"


SavePoint::SavePoint()
{

}

SavePoint::SavePoint(D3DXVECTOR3 &ipos) :GameStaticObject(ipos, TXTID_SAVEPOINT)
{
	
}

VOID SavePoint::SetStat(short is)
{
	if (stat == 0) stat = is;
	SoundManager::GetInstance()->PlayWaveFile(SOUND_SAVE); 
}

RESULT SavePoint::UpdateSub()
{
	if (stat == 0) return Default;
	if (stat == 1) {
		frame = 0; stat = 2;
	}
	else if (stat == 2) {
		frame++; if (frame >= 30) {
			stat = 3;
			D3DXVECTOR3 ipos(pos);
			ipos.x += (Volume.front().left + Volume.front().right) / 2;
			ipos.y += (Volume.front().top + Volume.front().bottom) / 2;
			auto input = new EnemyBullet(ipos, TXTID_PARTICLE_2X2);
			input->velocity.x = 4.0f;
			float dt = (SystemManager::GetInstance()->GetPlayer()->pos.x - ipos.x) / 4;
			if (dt <= 0) { input->velocity.x *= -1; dt *= -1; }
			input->velocity.y = (SystemManager::GetInstance()->GetPlayer()->pos.y - ipos.y) / dt -
				(0.5f * dt * 0.28f);
			if (input->velocity.y <= -5.0f)input->velocity.y = -5.0f;
			input->acceleration.y = 0.28f;
			input->PushBackVolume(FRECT{ 0,2,0,2 });
			input->PushBackVolume(FRECT{ 0,2,0,2 });
			SystemManager::GetInstance()->AddEnemyBullet(input);
		}
	}
	else if (stat == 3) { frame--; if (frame <= 0) {stat = 0; frame = 0; }}
	dir = frame / 4; if (frame >= 28)dir = 6;
	return Default;
}
VOID SavePoint::SetComponent()
{
	Volume.push_back(FRECT{ 0,16,0,16 });

	Volume.push_back(FRECT{ 0,16,0,16 });
	stat = 0;
	frame = 0;
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}
RENDERSQUARE SavePoint::GetRenderSquare()
{
	return RENDERSQUARE{ dir,0 };
}
SavePoint::~SavePoint()
{
}
