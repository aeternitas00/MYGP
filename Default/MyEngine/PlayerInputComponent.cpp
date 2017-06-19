#include "stdafx.h"
#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent()
{
}

PlayerInputComponent::~PlayerInputComponent()
{
}

VOID PlayerInputComponent::Update(GameObject* pObj)
{
	Player* temp = dynamic_cast<Player*>(pObj);
	if (temp == NULL) return;

	if (!temp->IsRTgl()) {
		if (KEY_DOWN(0x52)) {
			GET_SYSMANAGER()->LoadSF(); temp->SetRToggle(true);
		}
	}
	else {
		if (KEY_UP(0x52))
			temp->SetRToggle(false);
	}

	if (pObj->txtid == -1) return;

	if (!temp->IsLeftTgl()) {
		if (KEY_DOWN(VK_LEFT))
			temp->MovingLeft();
	}
	else {
		if (KEY_UP(VK_LEFT))
			temp->MovingLeftStop();
	}


	if (KEY_DOWN(0x51)) {
		temp->DoDeath();
	}


	if (!temp->IsRightTgl()) {
		if (KEY_DOWN(VK_RIGHT)) 
			temp->MovingRight();
	}
	else {
		if (KEY_UP(VK_RIGHT))
			temp->MovingRightStop();
	}

	if (KEY_DOWN(0x5A)) {
			temp->Jump();
	}
	if (temp->IsUpTgl()) { if (KEY_UP(0x5A)) temp->JumpingStop(); }

	if (!temp->IsAttackTgl()) {
		if (KEY_DOWN(0x58/*x Key*/)) {	temp->Attack();	}
	}
	else { if (KEY_UP(0x58)) temp->AttackStop(); }


}