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
		Volume=FRECT{ 0,31,0,31 };
	}
	MyPolygon temp;
	switch (dir) {
	case CToUp:
		temp.push_back(D3DXVECTOR2(15.5, 0));
		temp.push_back(D3DXVECTOR2(0, 31));
		temp.push_back(D3DXVECTOR2(31, 31));
		satvolume.push_back(temp);
		break;
	case CToDown:
		temp.push_back(D3DXVECTOR2(0, 0));
		temp.push_back(D3DXVECTOR2(31, 0));
		temp.push_back(D3DXVECTOR2(15.5, 31));
		satvolume.push_back(temp);
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

RENDERSQUARE Spike::GetRenderSquare()
{
	return RENDERSQUARE{dir,0};
}

VOID Spike::SetComponent()
{
	ComponentList.push_back(new GraphicsComponent);
}
