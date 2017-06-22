#include "stdafx.h"
#include "PlayerPhysicsComponent.h"

RESULT PlayerPhysicsComponent::Update(GameObject * pObj)
{
	Player* temp = dynamic_cast<Player*>(pObj);
	if (temp == NULL) return Default;
	if (pObj->txtid == -1) return Default;

	FRECT volume = temp->GetVolume();

	
	auto TerrainList = GET_LIST_OUT(GameTerrain);
	auto ObstacleList = GET_LIST_OUT(Obstacle);
	auto EnemyBulletList = GET_LIST_OUT(EnemyBullet);
	auto PlatformList = GET_LIST_OUT(Platform);
	auto EnemyList = GET_LIST_OUT(Enemy);
	if (temp->IsMoving())
	{
		if (temp->GetMovingLeft() == 1) temp->velocity.x = -2.0f;
		else if (temp->GetMovingRight() == 1) temp->velocity.x = 2.0f;
	}
	else { temp->velocity.x = 0; }

	if (temp->IsLanded()) temp->velocity.y = 0;
	if (temp->IsJumping() && temp->GetRemainJump() >= 0) 
		{ temp->velocity.y = -5.3f; temp->SetJumpingStat(false); if (temp->IsLanded()) temp->SetLandedStat(false); }
	if (temp->IsJumpingUp())
		{ if (temp->velocity.y > 0) temp->SetJumpingUpStat(false); temp->velocity.y -= 0.495f; }
	if (temp->velocity.y > 4.75f) 
		{ temp->velocity.y = 4.75f; }

	temp->velocity += temp->acceleration;
	if (temp->IsGravityOn())temp->velocity.y += 0.76f;
	temp->pos += temp->velocity;

	FRECT rect;
	float landpos;
	bool landok = false;

	rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
	rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;

	for (auto it : *TerrainList)
	{
		if (it->pos.x < rect.right && it->GetXEnd() > rect.left) {

			if (!it->IsThroughable()) {
				if (!(it->pos.x < rect.right - temp->velocity.x)) {
					if (it->pos.y < rect.bottom && it->GetYEnd() > rect.top)
					{
						temp->pos.x -= (rect.right - it->pos.x);
						rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
						rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;
					}
				}
				else if (!(it->GetXEnd() > rect.left - temp->velocity.x)) {
					if (it->pos.y < rect.bottom && it->GetYEnd() > rect.top)
					{
						temp->pos.x -= (rect.left - it->GetXEnd());
						rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
						rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;
					}
				}
			}
		}

		if (it->pos.x < rect.right && it->GetXEnd() > rect.left) {
			if (it->pos.y + temp->velocity.y >= rect.bottom && it->pos.y <= rect.bottom)
			{
				landpos=it->pos.y; landok = true; 
			}
			if (!it->IsThroughable()) {
				if (it->GetYEnd() + temp->velocity.y <= rect.top && it->GetYEnd() >= rect.top)
				{
					temp->pos.y = it->GetYEnd()-volume.top; temp->velocity.y = 0.0f;
				}
			}
		}
	}

	rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
	rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;

	for (auto it : *PlatformList)
	{
		if (it->pos.x < rect.right && it->GetXEnd() > rect.left) {
						
			if (!(it->pos.x < rect.right - temp->velocity.x)) {
				if (it->pos.y < rect.bottom && it->GetYEnd() > rect.top)
				{
					temp->pos.x -= (rect.right - it->pos.x);
					rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
					rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;
				}
			}
			else if (!(it->GetXEnd() > rect.left - temp->velocity.x)) {
				if (it->pos.y < rect.bottom && it->GetYEnd() > rect.top)
				{
					temp->pos.x -= (rect.left - it->GetXEnd());
					rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
					rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;
				}
			}
			
		}

		if (it->pos.x < rect.right && it->GetXEnd() > rect.left) {
			if (it->pos.y + temp->velocity.y - it->GetVel().y >= rect.bottom && it->pos.y <= rect.bottom)
			{
				landpos = it->pos.y; landok = true;
				if (it->IsMoving()&&it->InRange()) {
					temp->pos += it->GetVel();
					landpos += it->GetVel().y;
				}
			}
			if (it->GetYEnd() + temp->velocity.y <= rect.top && it->GetYEnd() >= rect.top)
			{
				temp->pos.y = it->GetYEnd() - volume.top; temp->velocity.y = 0.0f;
			}
		}
	}

	rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
	rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;
	
	for (auto it : *ObstacleList)
	{
		if (CollisionDetection(temp, it))
		{
			temp->DoDeath(); return Default;
		}
	}

	for (auto it : *EnemyBulletList)
	{
		if(CollisionDetection(temp, it))
		{
			temp->DoDeath(); return Default;
		}
	}

	for (auto it : *EnemyList)
	{
		if (CollisionDetection(temp, it))
		{
			temp->DoDeath(); return Default;
		}
	}

	if (landok)	{
		if (!temp->IsLanded()) { temp->pos.y = landpos - volume.bottom; temp->velocity.y = 0; 
		temp->DisableGravity(); temp->SetLanded(); 
		SoundManager::GetInstance()->PlayWaveFile(SOUND_LAND);}
	}

	else {	if (temp->IsLanded()) 	{ temp->EnableGravity(); temp->SetFloated(); } }


	if (rect.left+3.0f<0){
		if (GET_SYSMANAGER()->IsMovableSideOfScene(CToLeft)) {
			temp->pos.x = MAX_X - volume.right - 11.0f;
			GET_SYSMANAGER()->SendMyMessage(CToLeft);
		}
		else
			temp->pos.x = 0 - volume.left;
	}
	else if (rect.right>MAX_X-7.0f) {
		if (GET_SYSMANAGER()->IsMovableSideOfScene(CToRight)) {
			temp->pos.x = 0 - volume.left-3.0f;
			GET_SYSMANAGER()->SendMyMessage(CToRight);
		}
		else
			temp->pos.x = MAX_X - volume.right-10.0f;
	}
	if (rect.top<0) {
		if (GET_SYSMANAGER()->IsMovableSideOfScene(CToUp)) {
			temp->pos.y = MAX_Y - volume.bottom - 1.0f;
			GET_SYSMANAGER()->SendMyMessage(CToUp);
		}
		else
			temp->pos.y = 0.0f - volume.top;
	}
	else if (rect.bottom>MAX_Y-20) {
		if (GET_SYSMANAGER()->IsMovableSideOfScene(CToDown)) {
			temp->pos.y = 0.0f + volume.top + 1.0f;
			GET_SYSMANAGER()->SendMyMessage(CToDown);
		}
		else {
			temp->DoDeath();
		}
	}
	return Default;
}

PlayerPhysicsComponent::PlayerPhysicsComponent()
{

}


PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}
