#include "stdafx.h"
#include "IntroCharacter.h"

VOID IntroCharacter::SetComponent()
{
	ComponentList.push_back(new IntroScript);
	ComponentList.push_back(new PhysicsComponent);
	ComponentList.push_back(new GraphicsComponent);
}

IntroCharacter::IntroCharacter() :status(1),
GameMovableObject(D3DXVECTOR3(-80, MAX_Y - 102, 0), D3DXVECTOR3(0.85f, 0, 0), D3DXVECTOR3(0, 0, 0), TXTID_INTROKID + 1)
{
}


IntroCharacter::~IntroCharacter()
{
}

RENDERSQUARE IntroCharacter::GetRenderSquare()
{
	int x = 0, y = 0;

	static short stat1 = 0;
	static bool increase1 = true;
	static short stat2 = 0;
	static bool increase2 = true;
	if (status==0) {
		if (stat1 >= 26) increase1 = false; else if (stat1 <= 0)increase1 = true;
		if (increase1)stat1++; else stat1--;
		if (stat1 >= 0 && stat1 <= 13)x = 0;
		else x = 1;
	}
	else if (status==1) {
		if (stat2 >= 29) increase2 = false; else if (stat2 <= 0)increase2 = true;
		if (increase2)stat2++; else stat2--;
		if (stat2 >= 0 && stat2 <= 4) x += 2;
		else if (stat2 >= 4 && stat2 <= 10) x += 3;
		else if (stat2 >= 11 && stat2 <= 17) x += 4;
		else if (stat2 >= 18 && stat2 <= 24) x += 5;
		else if (stat2 >= 25 && stat2 <= 29) x += 6;
	}
	else if (status == 2) {
		x = 1;
	}
	return RENDERSQUARE{ x, y };
}
