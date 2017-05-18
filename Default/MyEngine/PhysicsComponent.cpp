#include "stdafx.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
	volume.bottom = 0;
	volume.top = 0;
	volume.left = 0;
	volume.right = 0;
}

bool PhysicsComponent::CollisionCheck(const FRECT one, const FRECT two)
{
	if ((one.left <= two.right &&one.left >= two.left)|| 
		(one.right >= two.left&&one.right <= two.right)) {
		if ((one.top <= two.bottom &&one.top >= two.top) ||
			(one.bottom >= two.top&&one.bottom <= two.bottom)) {
			return true;
		}
	}
	if (one.left <= two.left &&one.right >= two.right)  {
		if (one.top <= two.top &&one.bottom>= two.bottom) {
			return true;
		}
	}
	if (one.left >= two.left &&one.right <= two.right) {
		if (one.top >= two.top &&one.bottom <= two.bottom) {
			return true;
		}
	}

	return false;
}

bool PhysicsComponent::CollisionCheck(D3DXVECTOR3& pone, D3DXVECTOR3& ptwo, std::list<FRECT>& vlone, std::list<FRECT>& vltwo)
{
	for (auto it2 : vlone) {
		FRECT obsrect = it2;
		obsrect.top += pone.y;	obsrect.bottom += pone.y;
		obsrect.left += pone.x;	obsrect.right += pone.x;
		for (auto it3 : vltwo) {
			FRECT plrect = it3;
			plrect.top += ptwo.y; plrect.left += ptwo.x;
			plrect.bottom += ptwo.y; plrect.right += ptwo.x;
			if (CollisionCheck(obsrect, plrect))
				return true;
		}
	}
	return false;
}

VOID PhysicsComponent::Update(GameObject* pObj)
{
	GameMovableObject* temp = dynamic_cast<GameMovableObject*>(pObj);
	if (temp == NULL) return;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;
	//if (temp->pos.y >= 300) { temp->pos.y = 300; temp->velocity.y = 0; } // юс╫ц

	//resolveCollision();
	return;
}

PhysicsComponent::~PhysicsComponent()
{
}
