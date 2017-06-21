#include "stdafx.h"
#include "MovingPlatform.h"


MovingPlatform::MovingPlatform():moving(false),frame(0)
{
}


VOID MovingPlatform::Initialize(char * n)
{
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	txtid = atoi(strtok_s(NULL, " ", &temp));
	sensor.top = atoi(strtok_s(NULL, " ", &temp));
	sensor.bottom = atoi(strtok_s(NULL, " ", &temp));
	sensor.left = atoi(strtok_s(NULL, " ", &temp));
	sensor.right = atoi(strtok_s(NULL, " ", &temp));
	velocity.x = atoi(strtok_s(NULL, " ", &temp));
	velocity.y = atoi(strtok_s(NULL, " ", &temp));
	type = atoi(strtok_s(NULL, " ", &temp));
	maxframe = atoi(strtok_s(NULL, " ", &temp));
	SetComponent();
}

MovingPlatform::~MovingPlatform()
{
}

RESULT MovingPlatform::UpdateSub()
{
	auto player = GET_SYSMANAGER()->GetPlayer();
	auto rect = player->GetVolume();
	rect.left += player->pos.x; rect.right += player->pos.x;
	rect.top += player->pos.y; rect.bottom += player->pos.y;
	PhysicsComponent temp;
	switch (type) {
	case 0:
		if (temp.CollisionCheck(rect, sensor))
			moving = true;
		else
			moving = false;
		if (moving) {
			if (frame < maxframe) {
				frame++;pos += velocity;
				sensor.left += velocity.x; sensor.right+= velocity.x;
				sensor.bottom += velocity.y; sensor.top += velocity.y;
			}
		}
		else {
			if (frame >0) {
				frame--; pos -= velocity;
				sensor.left -= velocity.x; sensor.right -= velocity.x;
				sensor.bottom -= velocity.y; sensor.top -= velocity.y;
			}
		}
		break;
	}
	
	return Default;
}



VOID MovingPlatform::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}

