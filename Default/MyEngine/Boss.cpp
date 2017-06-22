#include "stdafx.h"
#include "Boss.h"


RENDERSQUARE Boss::GetRenderSquare()
{
	RENDERSQUARE rv = { 0,0 };
	if (tlfr)rv.y = 0;
	else rv.y = 1;
	frame++;
	if (frame == 24)frame = 0;
	switch (stat)
	{
	case 0:
		if (frame >= 0 && frame <= 5) rv.x += 0;
		else if (frame >= 6 && frame <= 11) rv.x += 1;
		else if (frame >= 12 && frame <= 17) rv.x += 2;
		else if (frame >= 18 && frame <= 23) rv.x += 3;
		break;
	case 1:
		rv.x = 4;
		if (frame >= 0 && frame <= 4) rv.x += 3;
		else if (frame >= 5 && frame <= 9) rv.x +=0;
		else if (frame >= 10 && frame <= 14) rv.x += 2;
		else if (frame >= 15 && frame <= 19) rv.x += 1;
		else if (frame >= 20 && frame <= 23) rv.x += 4;
		break;
	case 2:
		rv.x = 9;
		if (frame >= 0 && frame <= 5) rv.x += 0;
		else if (frame >= 6 && frame <= 11) rv.x += 1;
		else if (frame >= 12 && frame <= 17) rv.x += 0;
		else if (frame >= 18 && frame <= 23) rv.x += 1;
		break;
	}
	return rv;
}

RESULT Boss::UpdateSub()
{
	if (txtid == -1)
	{
		frame++;
		if (frame == 100) {
			GET_SYSMANAGER()->SendMyMessage(10);
		}
	}
	return Default;
}

VOID Boss::SetComponent()
{
	MyPolygon temppol;
	temppol.push_back(D3DXVECTOR2(20, 5));
	temppol.push_back(D3DXVECTOR2(78, 5));
	temppol.push_back(D3DXVECTOR2(78, 82));
	temppol.push_back(D3DXVECTOR2(20, 82));
	PushBackSATVolume(temppol);
	hp = 10;
	txtid = 12;
	ComponentList.push_back(new BossPhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
	ComponentList.push_back(new BossScript);
}

VOID Boss::GetHitted()
{
	GET_SNDMANAGER()->PlayWaveFile(SOUND_BOSSHIT);
	hp--;
	if (hp == 0) { DoDeath(); frame = 0; }
}

VOID Boss::DoDeath() 
{
	txtid = -1;
	
}
Boss::Boss()
{
	tlfr = true;
	stat = 2;
	pos.x = 640;
	pos.y = 300;
	velocity.x = -3.5f;
	velocity.y = -4.5f;
	acceleration.y = 0.225f;
}


Boss::~Boss()
{
}
