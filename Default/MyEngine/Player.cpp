#include "stdafx.h"
#include "Player.h"


VOID Player::SetComponent()
{
	ComponentList.push_back(new PlayerInputComponent);
	ComponentList.push_back(new PlayerPhysicsComponent);
	ComponentList.push_back(new PlayerGraphicsComponent);

}

VOID Player::Jump()
{
	if (!jumping_tgl) { gravity = true; jumping_tgl = true; jumping = true; jumping_up = true; 
	if (remain_jump == 1)SoundManager::GetInstance()->PlayWaveFile(SOUND_DOUBLEJUMP); 
		remain_jump--; }
}

VOID Player::Attack()
{
	attack = true;	attack_tgl = true;
	GET_SYSMANAGER()->AddPlayerBullet(new PlayerBullet(this));
	SoundManager::GetInstance()->PlayWaveFile(SOUND_FIRE);
	attack_rmt = 18;
}

VOID Player::DoDeath()
{
	txtid = -1;
	GET_SNDMANAGER()->StopWaveFile();
	GET_SNDMANAGER()->PlayWaveFile(1005);
	GET_SNDMANAGER()->PlayWaveFile(1006);
	
	auto temp =GET_SYSMANAGER();
	srand(time(NULL));
	D3DXVECTOR3 ipos(pos);
	ipos.x += float(Volume.left + Volume.right) / 2;
	ipos.y += float(Volume.top + Volume.bottom) / 2;
	for (int i = 0; i < 100; i++)
	{
		D3DXVECTOR3 vel((float)(rand()%17000)/1000-8.5f, (float)(rand() % 17000)/1000 - 11.0f,0);
		temp->AddObject(new Particle(ipos,vel, D3DXCOLOR(1,0,0,1),TXTID_PARTICLE_4X4));
	}
	Enemy* tobj = new Enemy(D3DXVECTOR3(MAX_X / 2 - (550 / 2), MAX_Y / 2 - 130, 0), TXTID_GAMEOVER);
	tobj->SetComponent();
	tobj->AddComponent(new ObjectShake(0.25, 20000, 0, D3DXVECTOR3(MAX_X / 2 - (550 / 2), MAX_Y / 2 - 130, 0)));
	GET_LIST_OUT(Enemy)->push_back(tobj);
}


RENDERSQUARE Player::GetRenderSquare()
{
	int x = 0, y = 0;

	static short stat=0;
	static bool increase = true;

	if (stat >= 31) increase = false; else if (stat <= 0)increase = true;
	if (increase)stat++; else stat--;

	if (go_right==1) y = 0;
	else if (go_left==1) y = 1;
	

	if (moving==0) {
		if (!landed)
		{
			if(attack) x=9;
			else x = 8;
		}
		else { if (attack) x = 4;else x = 0; }
	}
	else if (moving!=0) {
		if (!landed) {
			if(attack)x=9;	else x = 8;
		}
		else {
			if(attack)x = 4;
			if (stat >= 0 && stat <= 7) x += 1;
			else if (stat >= 8 && stat <= 23) x += 2;
			else if (stat >= 24 && stat <= 31) x += 3;
		}
	}
	return RENDERSQUARE{ x, y };
}

Player::Player(D3DXVECTOR3 & ipos):GameMovableObject(ipos,
	D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), TXTID_PLAYER),
	go_left(0), go_right(1), left_tgl(false), moving(0), right_tgl(false),
	jumping_tgl(false), jumping_up(false), jumping(false), attack(false), attack_tgl(false), remain_jump(1), landed(false),
	attack_rmt(0), gravity(true)
{

	Volume=FRECT{ 15,30,12,27 };

	MyPolygon temp;
	temp.push_back(D3DXVECTOR2(17,13));
	temp.push_back(D3DXVECTOR2(10,28));
	temp.push_back(D3DXVECTOR2(25,28));
	satvolume.push_back(temp);
}

Player::~Player()
{
}

RESULT Player::UpdateSub()
{
	if (txtid == -1) return Default;
	attack_rmt >= 0 ? attack_rmt-- : attack = false;
	return Default;
}

VOID Player::MovingLeft() {
	if (go_right == 1) { if (right_tgl) go_right++; else go_right=0; }
	if (go_left!=1)go_left++;	moving++;
	left_tgl = true;
}

VOID Player::MovingRight() { 
	if (go_left==1 ) { if (left_tgl) go_left++; else go_left = 0; }
	if (go_right != 1)go_right++;	moving++;
	right_tgl = true; 
}

VOID Player::MovingLeftStop() {
	if (go_right == 2) { go_left--; go_right--; }
	else if (go_right == 1) go_left = 0; left_tgl = false; moving--;
}

VOID Player::MovingRightStop() {
	if (go_left == 2) { go_left--; go_right--; }
	else if (go_left == 1) go_right = 0; right_tgl = false; moving--;
}
