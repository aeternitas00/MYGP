#include "stdafx.h"
#include "BossPhysicsComponent.h"


BossPhysicsComponent::BossPhysicsComponent()
{
}


BossPhysicsComponent::~BossPhysicsComponent()
{
}

RESULT BossPhysicsComponent::Update(GameObject * pObj)
{
	Boss* temp = dynamic_cast<Boss*>(pObj);
	if (temp == NULL) return Default;
	if (temp->txtid == -1)return Default;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	auto PlayerBulletList = GET_LIST_OUT(PlayerBullet);
	for (auto it : *PlayerBulletList)
	{
		if (CollisionDetection(temp, it))
		{
			temp->GetHitted(); it->SetStat(Destroy);
		}
	}
}
