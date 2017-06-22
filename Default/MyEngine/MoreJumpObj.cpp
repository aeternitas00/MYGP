#include "stdafx.h"
#include "MoreJumpObj.h"


MoreJumpObj::MoreJumpObj():resettimer(0),frame(0),updown(true)
{
}


MoreJumpObj::~MoreJumpObj()
{
}

RESULT MoreJumpObj::UpdateSub()
{
	if (resettimer == 0) {
		auto player = GET_SYSMANAGER()->GetPlayer();
		auto rect = player->GetVolume();
		rect.left += player->pos.x; rect.right += player->pos.x;
		rect.top += player->pos.y; rect.bottom += player->pos.y;
		auto rect2 = Volume;
		rect2.left += pos.x;		rect2.right += pos.x;
		rect2.top += pos.y;		rect2.bottom += pos.y;
		PhysicsComponent temp;
		if (temp.CollisionCheck(rect, rect2)) {
			player->SetRemainJump(1); txtid = -1; resettimer = 200;
		}
		if (updown) { pos.y += 0.15f; frame++; if (frame > 15) updown = false; }
		else { pos.y -= 0.15f; frame--; if (frame < 0) updown = true; }
	}
	else {
		resettimer--; if (resettimer == 0)txtid = TXTID_MOREJUMP;
	}
	return Default;
}

VOID MoreJumpObj::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = TXTID_MOREJUMP;
	SetComponent();
	Volume.bottom = 9; Volume.right = 9;
	Volume.top = 0; Volume.left = 0;
}

VOID MoreJumpObj::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}
