#include "stdafx.h"
#include "Player.h"

Player::Player():GameMovableObject(D3DXVECTOR3(0,0,0),D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),TXTID_PLAYER)
{
}

Player::~Player()
{
}

VOID Player::update()
{
	GameMovableObject::update();
}
