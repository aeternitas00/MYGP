#include "stdafx.h"
#include "SavePoint.h"


SavePoint::SavePoint()
{

}

SavePoint::SavePoint(D3DXVECTOR3 &ipos) :GameStaticObject(ipos, TXTID_SAVEPOINT)
{
	
}

VOID SavePoint::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = TXTID_SAVEPOINT;
	SetComponent();
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
			ipos.x += (Volume.left + Volume.right) / 2;
			ipos.y += (Volume.top + Volume.bottom) / 2;
			auto input = new EnemyBullet(ipos, TXTID_PARTICLE_2X2, false);
			input->velocity.x = 4.0f;
			float dt = (GET_SYSMANAGER()->GetPlayer()->pos.x - ipos.x) / 4;
			if (dt <= 0) { input->velocity.x *= -1; dt *= -1; }
			input->velocity.y = (GET_SYSMANAGER()->GetPlayer()->pos.y - ipos.y) / dt -
				(0.5f * dt * 0.28f);
			if (input->velocity.y <= -5.0f)input->velocity.y = -5.0f;
			if (input->velocity.y >= 5.0f)input->velocity.y = 5.0f;
			input->acceleration.y = 0.28f;

			MyPolygon temppol;
			temppol.push_back(D3DXVECTOR2(0, 0));
			temppol.push_back(D3DXVECTOR2(2, 0));
			temppol.push_back(D3DXVECTOR2(2, 2));
			temppol.push_back(D3DXVECTOR2(0, 2));
			input->PushBackSATVolume(temppol);
			GET_SYSMANAGER()->AddEnemyBullet(input);
		}
	}
	else if (stat == 3) { frame--; if (frame <= 0) {stat = 0; frame = 0; }}
	dir = frame / 4; if (frame >= 28)dir = 6;
	return Default;
}
VOID SavePoint::SetComponent()
{
	Volume=FRECT{ 0,16,0,16 };
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
