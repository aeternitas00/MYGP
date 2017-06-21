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

RESULT PhysicsComponent::Update(GameObject* pObj)
{
	GameMovableObject* temp = dynamic_cast<GameMovableObject*>(pObj);
	if (temp == NULL) return Default;

	temp->velocity += temp->acceleration;
	temp->pos += temp->velocity;

	return Default;
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

	// 최적화 위해 폴리곤 수가 적은 것을 먼저 하도록 고름

	for (auto polA : sObj->GetSATVolume())
	{
		for (auto polB : dObj->GetSATVolume())
		{
			if (ObjA->pos.x <= 507 && ObjA->pos.y <= 255.690003) {
				int a = 0;
			}
			MyPolygon sPol, dPol;
			D3DXVECTOR2 sCVec, dCVec;
			float sAngle, dAngle;
			if (polA.size() >= polB.size())
			{
				sPol = polB; sAngle = dObj->angle;
				sCVec.x = dObj->pos.x; sCVec.y = dObj->pos.y;
				dPol = polA; dAngle = sObj->angle;
				dCVec.x = sObj->pos.x; dCVec.y = sObj->pos.y;
			}
			else {
				sPol = polA; sAngle = sObj->angle;
				sCVec.x = sObj->pos.x; sCVec.y = sObj->pos.y;
				dPol = polB; dAngle = dObj->angle;
				dCVec.x = dObj->pos.x; dCVec.y = dObj->pos.y;
			}

			// 최적화 위해 축 수가 적은 것을 먼저 하도록 고름

			if (ComparePolygon(sPol, dPol, sCVec, dCVec, sAngle, dAngle)) {
				if (ComparePolygon(dPol, sPol, dCVec, sCVec, dAngle, sAngle))
					return true;
			}
		}
	}
	return false;
}


bool PhysicsComponent::ComparePolygon(MyPolygon& sPol, MyPolygon& dPol, D3DXVECTOR2&sCVec, D3DXVECTOR2& dCVec,float sAngle,float dAngle)
{
	auto sNode = sPol.back();
	sNode += sCVec;

	for (auto NextNode : sPol)
	{
		NextNode += sCVec;

		D3DXVECTOR2 Vector = NextNode - sNode;

		float Angle = D3DX_PI - atan2(Vector.y, Vector.x);

		float sMin, sMax, dMin, dMax;
		sMin = GetMinY(sPol, Angle, sNode, sCVec);
		sMax = GetMaxY(sPol, Angle, sNode, sCVec);
		dMax = GetMaxY(dPol, Angle, sNode, dCVec);
		dMin = GetMinY(dPol, Angle, sNode, dCVec);

		if ((!(sMin <= dMin && dMin <= sMax) && (!(sMin <= dMax&& dMax <= sMax)))) {
			if ((!(dMin <= sMin && sMin <= dMax) && !(dMin <= sMax&& sMax <= dMax))) {
				return false;
			}
		}
		sNode = NextNode;
	}
	return true;
}

D3DXVECTOR2 PhysicsComponent::RotatenMove(D3DXVECTOR2 & ivec, float Angle, D3DXVECTOR2 & center)
{
	auto rv = ivec;
	rv -= center;

	auto sina= sin(Angle);
	auto cosa = cos(Angle);
	if (Angle == D3DX_PI || Angle==-D3DX_PI) sina = 0;
	if (Angle == D3DX_PI/2 || Angle == -D3DX_PI/2)cosa = 0;
	float tx = rv.x*cosa - rv.y*sina;
	float ty = rv.y*cosa + rv.x*sina;

	rv.x = tx; rv.y = ty;
	if (rv.x < 0.00001&&rv.x>-0.00001) rv.x = 0;
	if (rv.y < 0.00001&&rv.y> -0.00001) rv.y = 0;
	return rv;
}

float PhysicsComponent::GetMaxY(MyPolygon& pol, float Angle, D3DXVECTOR2& center, D3DXVECTOR2& objpos)
{
	auto prev = ----pol.end();
	auto tprev = *prev;

	auto cur = --pol.end();
	auto tcur = *cur;

	tprev += objpos;
	tcur += objpos;

	auto rprev = RotatenMove(tprev, Angle, center);
	auto rcur = RotatenMove(tcur, Angle, center);

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
	auto tprev = *prev;

	auto cur = --pol.end();
	auto tcur = *cur;

	tprev+=objpos;
	tcur += objpos;

	auto rprev = RotatenMove(tprev, Angle, center);
	auto rcur = RotatenMove(tcur, Angle, center);

	for (auto next = pol.begin(); next != pol.end(); next++)
	{
		D3DXVECTOR2 tnext = *next;
		tnext += objpos;
		auto rnext = RotatenMove(tnext, Angle, center);
		if (rprev.y >= rcur.y &&rnext.y > rcur.y)
		{
			if (rcur.y < 0) 
			{ int a = 0; }
			return rcur.y;
		}
		tprev = tcur;
		tcur = tnext;
		rprev = rcur;
		rcur = rnext;
	}
}

PhysicsComponent::~PhysicsComponent()
{
}
