#pragma once
#include "stdafx.h"

class Player :
	public GameMovableObject
{
private:
	short go_left, go_right;
	bool left_tgl,right_tgl;
	short moving;

	bool jumping_up, jumping, jumping_tgl, landed;
	short remain_jump;

	bool attack, attack_tgl;
	int attack_rmt;

	bool gravity;
public:
	Player();
	Player(D3DXVECTOR3& ipos);
	~Player();

	virtual RESULT Update();

	VOID MovingLeft();
	VOID MovingRight();
	VOID MovingLeftStop();
	VOID MovingRightStop();

	VOID SetLeft(int ia) {}

	VOID Jump();
	VOID JumpingStop() { jumping_tgl = false; jumping_up = false; }
	VOID SetLanded() { jumping = false; landed = true; remain_jump = 2; jumping_up = false;	}
	VOID SetFloated() { landed = false; remain_jump = 1; }
	VOID SetLandedStat(bool il) { landed = il; }
	VOID SetJumpingStat(bool il){ jumping = il; }
	VOID SetJumpingUpStat(bool il) { jumping_up = il; }

	VOID EnableGravity() { gravity = true;  }
	VOID DisableGravity() { gravity = false;  }

	VOID Attack();
	VOID AttackStop() { attack_tgl = false; }

	inline	short IsMoving() { return moving; }
	inline	bool IsLeftTgl() { return left_tgl; }
	inline	bool IsRightTgl() { return right_tgl; }
	inline	bool IsUpTgl() { return jumping_tgl; }
	inline	bool IsJumping() { return jumping; }
	inline	short GetRemainJump() { return remain_jump; }
	inline	short GetMovingLeft() { return go_left; }
	inline	short GetMovingRight() { return go_right; }
	inline	bool IsAttackTgl() { return attack_tgl; }
	inline	bool IsGravityOn() { return gravity; }
	inline	bool IsLanded() { return landed; }
	inline	bool IsJumpingUp() { return jumping_up; }
	inline	bool IsAttacking() { return attack_rmt >= 0; }

	short GetDir() { if (go_left == 1) return -1; else if (go_right == 1)return 1; }
	RENDERSQUARE GetRenderSquare();
	virtual VOID SetComponent();
};

