#include "stdafx.h"
#include "FakeSpike.h"


FakeSpike::FakeSpike() :moving(false)
{
}


VOID FakeSpike::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	dir = atoi(strtok_s(NULL, " ", &temp));
	txtid = TXTID_SPIKE;
	sensor.top = atoi(strtok_s(NULL, " ", &temp));
	sensor.bottom = atoi(strtok_s(NULL, " ", &temp));
	sensor.left = atoi(strtok_s(NULL, " ", &temp));
	sensor.right = atoi(strtok_s(NULL, " ", &temp));
	velocity.x = atoi(strtok_s(NULL, " ", &temp));
	velocity.y = atoi(strtok_s(NULL, " ", &temp));
	SetVolume();
	SetComponent();
}

FakeSpike::~FakeSpike()
{
}

RESULT FakeSpike::UpdateSub()
{
	PhysicsComponent temp;
	auto player= GET_SYSMANAGER()->GetPlayer();
	auto rect = player->GetVolume();
	rect.left += player->pos.x;rect.right+= player->pos.x;
	rect.top += player->pos.y; rect.bottom += player->pos.y;
	if (temp.CollisionCheck(rect, sensor))
		moving = true;
	if (moving)pos += velocity;
	if (!IsInScreen())return Destroy;
	return Default;
}



VOID FakeSpike::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}
