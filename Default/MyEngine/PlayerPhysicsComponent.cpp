#include "stdafx.h"
#include "PlayerPhysicsComponent.h"


VOID PlayerPhysicsComponent::Update(GameObject * pObj)
{
	Player* temp = dynamic_cast<Player*>(pObj);
	if (temp == NULL) return;

	auto& TerrainList = SystemManager::GetInstance()->GetTerrainList();

	temp->SetVel();

	temp->velocity += temp->acceleration;
	if (temp->IsGravityOn())temp->velocity.y += 0.76;
	temp->pos += temp->velocity;

	RECT rect;
	float landpos;
	bool landok = false;

	rect.top = temp->pos.y + volume.top; rect.left = temp->pos.x + volume.left;
	rect.bottom = temp->pos.y + volume.bottom; rect.right = temp->pos.x + volume.right;

	for (auto it : TerrainList)
	{
		if (it->pos.x < rect.right && it->GetXEnd() > rect.left) {
			if (!(it->pos.x < rect.right - temp->velocity.x)) {
				if ((it->pos.y + it->GetYEnd()) > rect.top && it->pos.y < rect.bottom)
				{
					temp->pos.x -= (rect.right - it->pos.x);
				}
			}
			else if (!((it->pos.x + it->GetXEnd()) > rect.left - temp->velocity.x)) {
				if ((it->pos.y + it->GetYEnd()) > rect.top && it->pos.y < rect.bottom)
				{
					temp->pos.x -= (rect.left - (it->pos.x + it->GetXEnd()));
				}
			}
			if (it->pos.y + temp->velocity.y >= rect.bottom && it->pos.y <= rect.bottom)
			{
				landpos=it->pos.y; landok = true;
			}
		}
	}


	//resolveCollision();
	
	if (landok)	{
		if (!temp->IsLanded()) { temp->pos.y = landpos - volume.bottom; temp->velocity.y = 0; temp->DisableGravity(); temp->SetLanded(); }
	}

	else {	if (temp->IsLanded()) 	{ temp->EnableGravity(); temp->SetFloated(); } }

	// if (temp->IsLanded()) {	temp->pos.y = 300; temp->velocity.y = 0; temp->DisableGravity(); temp->SetLanded();	}//юс╫ц
	return;
}

PlayerPhysicsComponent::PlayerPhysicsComponent()
{
	volume.left = 20; volume.right = 60;
	volume.top = 14; volume.bottom = 61;
}


PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}
