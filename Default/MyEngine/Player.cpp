#include "stdafx.h"
#include "Player.h"

VOID Player::SetComponent()
{
	ComponentList.push_back(new PlayerInputComponent);
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new PlayerGraphicsComponent);
}

Player::Player():GameMovableObject(D3DXVECTOR3(20,20,0),D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),TXTID_PLAYER)
{
	SetComponent();
}

Player::~Player()
{
}
