#include "stdafx.h"
#include "PhysicsComponent.h"
#include <math.h>

PhysicsComponent::PhysicsComponent()
{

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

bool PhysicsComponent::CollisionDetection(GameObject* ObjA,GameObject* ObjB)
{
	GameObject* sObj, *dObj;
	if (ObjA->GetSATLength() >= ObjB->GetSATLength())
	{
		sObj = ObjB;
		dObj = ObjA;
	}
	else {
		sObj = ObjA;
		dObj = ObjB;
	}

	for (auto polA : sObj->GetSATVolume())
	{
		for (auto polB : dObj->GetSATVolume())
		{
			MyPolygon sPol, dPol;
			D3DXVECTOR2 sCVec, dCVec;
			if (polA.size() >= polB.size())
			{
				sPol = polB;
				sCVec.x = dObj->pos.x; sCVec.y = dObj->pos.y;
				dPol = polA;
				dCVec.x = sObj->pos.x; dCVec.y = sObj->pos.y;
			}
			else {
				sPol = polA;
				sCVec.x = sObj->pos.x; sCVec.y = sObj->pos.y;
				dPol = polB;
				dCVec.x = dObj->pos.x; dCVec.y = dObj->pos.y;
			}
			auto sNode = sPol.back();
			sNode += sCVec;

			for (auto NextNode : sPol)
			{
				NextNode += sCVec;

				D3DXVECTOR2 Vector = NextNode - sNode;
				
				double dAngle1 = atan2(Vector.x, Vector.y);
				double dAngle2 = atan2(1, 0);
				float Angle = dAngle2 - dAngle1;
				
				float sMin, sMax, dMin, dMax;
				sMin = GetMinY(sPol, Angle, sNode, sCVec);
				sMax = GetMaxY(sPol, Angle, sNode, sCVec);
				dMax = GetMaxY(dPol, Angle, sNode, dCVec);
				dMin = GetMinY(dPol, Angle, sNode, dCVec);

				if (!((sMin <= dMin && dMin <= sMax) || (sMin <= dMax&& dMax <= sMax))&&
					!((dMin <= sMin && sMin <= dMax) || (dMin <= sMax&& sMax <= dMax)))
					return false;
				sNode = NextNode;
			}
		}
	}
	return true;
}



D3DXVECTOR2 PhysicsComponent::RotatenMove(D3DXVECTOR2 & ivec, float Angle, D3DXVECTOR2 & center)
{
	auto rv = ivec;
	rv -= center;

	float tx = rv.x*cos(Angle) - rv.y*sin(Angle);
	float ty = rv.y*cos(Angle) + rv.x*sin(Angle);

	rv.x = tx; rv.y = ty;

	return rv;
}

float PhysicsComponent::GetMaxY(MyPolygon& pol, float Angle, D3DXVECTOR2& center, D3DXVECTOR2& objpos)
{
	auto prev = ----pol.end();
	auto rprev = *prev;

	auto cur = --pol.end();
	auto rcur = *cur;

	rprev += objpos;
	rcur += objpos;

	rprev = RotatenMove(rprev, Angle, center);
	rcur = RotatenMove(rcur, Angle, center);

	for (auto next = pol.begin(); next != pol.end(); next++)
	{
		D3DXVECTOR2 tnext = *next;
		tnext += objpos;
		auto rnext = RotatenMove(tnext, Angle, center);
		if (rprev.y <= rcur.y &&rnext.y < rcur.y)
			return rcur.y;
		rprev = rcur;
		rcur = rnext;
	}
}

float PhysicsComponent::GetMinY(MyPolygon& pol, float Angle, D3DXVECTOR2& center, D3DXVECTOR2& objpos)
{
	auto prev = ----pol.end();
	auto rprev = *prev;

	auto cur = --pol.end();
	auto rcur = *cur;

	rprev += objpos;
	rcur += objpos;

	rprev = RotatenMove(rprev, Angle, center);
	rcur = RotatenMove(rcur, Angle, center);

	for (auto next = pol.begin(); next != pol.end(); next++)
	{
		D3DXVECTOR2 tnext = *next;
		tnext += objpos;
		auto rnext = RotatenMove(tnext, Angle, center);
		if (rprev.y >= rcur.y &&rnext.y > rcur.y)
			return rcur.y;
		rprev = rcur;
		rcur = rnext;
	}
}

PhysicsComponent::~PhysicsComponent()
{
}
