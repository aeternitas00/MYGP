#include "stdafx.h"
#include "BossScript.h"


BossScript::BossScript():before(clock()), after(clock()), trigger(0),frame(0)
{
}

RESULT BossScript::Update(GameObject * pObj)
{
	if (trigger != -1) {
		Boss* Obj = dynamic_cast<Boss*>(pObj);
		if (Obj == NULL) return Default;
		if (Obj->txtid==-1) return Destroy;
		after = clock();
	
		switch (trigger)
		{
		case 0:
			if (Obj->pos.y > 404-82) 
			{ Obj->pos.y = 404 - 82; trigger = 1; frame = 0; 
			Obj->velocity.x = 0; Obj->velocity.y = 0; Obj->acceleration.y = 0;
			Obj->SetStat(0);
			}
			break;
		case 1:
			frame++;
			if (frame % 100==0)
			{
				D3DXVECTOR3 center=Obj->pos;
				center.x += 50-30.5; center.y += 41 - 30.5;
				D3DXVECTOR3 vec = GET_SYSMANAGER()->GetPlayer()->pos - center;
				vec.y -= 2;
				float size = sqrtf((vec.x*vec.x) + (vec.y*vec.y));
				vec.x /= size; vec.y /= size;
				vec.x *= 4; vec.y *= 4;
				EnemyBullet sample(center, TXTID_GUYBULLET, true);
				MyPolygon temppol;
				temppol.push_back(D3DXVECTOR2(16,0));
				temppol.push_back(D3DXVECTOR2(46, 0));
				temppol.push_back(D3DXVECTOR2(61, 16));
				temppol.push_back(D3DXVECTOR2(61, 46));
				temppol.push_back(D3DXVECTOR2(46, 61));
				temppol.push_back(D3DXVECTOR2(16, 61));
				temppol.push_back(D3DXVECTOR2(0, 46));
				temppol.push_back(D3DXVECTOR2(0, 16));
				sample.PushBackSATVolume(temppol);

				Obj->AddComponent(new BulletGenerate1(3, 6, vec, center, sample,SOUND_BOSSSHOOT));
				if (frame == 300) { trigger = 2; Obj->velocity.x =-1.5f; 
				Obj->SetStat(1); frame = -30;
				}
			}
			break;
		case 2:
			frame++;
			if (frame ==70)
			{
				D3DXVECTOR3 center = Obj->pos;
				center.x += 50 - 30.5; center.y += 41 - 30.5;
				D3DXVECTOR3 vec = GET_SYSMANAGER()->GetPlayer()->pos - center;
				vec.y -= 2;
				float size = sqrtf((vec.x*vec.x) + (vec.y*vec.y));
				vec.x /= size; vec.y /= size;
				vec.x *= 4; vec.y *= 4;
				EnemyBullet sample(center, TXTID_GUYBULLET, true);
				MyPolygon temppol;
				temppol.push_back(D3DXVECTOR2(16, 0));
				temppol.push_back(D3DXVECTOR2(46, 0));
				temppol.push_back(D3DXVECTOR2(61, 16));
				temppol.push_back(D3DXVECTOR2(61, 46));
				temppol.push_back(D3DXVECTOR2(46, 61));
				temppol.push_back(D3DXVECTOR2(16, 61));
				temppol.push_back(D3DXVECTOR2(0, 46));
				temppol.push_back(D3DXVECTOR2(0, 16));
				sample.PushBackSATVolume(temppol);

				Obj->AddComponent(new BulletGenerate1(1, 1, vec, center, sample, SOUND_BOSSSHOOT));

				frame = 0;
			}
			if (Obj->pos.x<30) {
				Obj->pos.x = 30;
				Obj->velocity.x = 0;
				Obj->SetStat(0);
				Obj->SetLook(false);
			}
				break;
		}
	}
	return Default;
}


BossScript::~BossScript()
{
}
