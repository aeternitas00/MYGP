#pragma once
#include "GameMovableObject.h"
class IntroCharacter :
	public GameMovableObject
{
	short status;
public:
	virtual VOID SetComponent();
	VOID SetStatus(short ib) { status = ib; }
	IntroCharacter();
	~IntroCharacter();
	virtual RENDERSQUARE GetRenderSquare();
};

