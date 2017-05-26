#pragma once
#include "GameStaticObject.h"
class SavePoint :
	public GameStaticObject
{
private:
	short stat;
	short frame;
public:
	SavePoint();
	SavePoint(D3DXVECTOR3&);
	VOID SetStat(short is);
	virtual RESULT UpdateSub();
	virtual VOID SetComponent();
	virtual RENDERSQUARE GetRenderSquare();
	~SavePoint();
};

