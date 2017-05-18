#include "stdafx.h"
#include "Spike.h"


Spike::Spike()
{
	txtid = -1;
}

Spike::Spike(D3DXVECTOR3 & ipos,int id,short idir)
{
	pos = ipos;
	txtid = id;
	dir = idir;
	
	if (id == TXTID_SPIKE) {
		Volume.push_back(FRECT{ 0,31,0,31 });
	}
	switch (dir) {
	case CToUp:
		Volume.push_back(FRECT{ 0,4,14,17 });
		Volume.push_back(FRECT{ 4,8,12,19 });
		Volume.push_back(FRECT{ 8,16,8,23 });
		Volume.push_back(FRECT{ 16,26,4,27 });
		Volume.push_back(FRECT{ 26,31,0,31 });
		break;
	case CToDown:
		Volume.push_back(FRECT{ 0,5,0,31 });
		Volume.push_back(FRECT{ 5,15,4,27 });
		Volume.push_back(FRECT{ 15,23,8,23 });
		Volume.push_back(FRECT{ 23,27,12,19 });
		Volume.push_back(FRECT{ 27,31,14,17 });
		break;
	case CToLeft:
		break;
	case CToRight:
		break;
	}
}


Spike::~Spike()
{
}

VOID Spike::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}
