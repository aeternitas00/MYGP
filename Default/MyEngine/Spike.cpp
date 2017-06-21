#include "stdafx.h"
#include "Spike.h"


Spike::Spike()
{
	txtid = -1;
}

VOID Spike::Initialize(char *n) {
	char* temp = NULL;
	pos.x = atoi(strtok_s(n, " ", &temp));
	pos.y = atoi(strtok_s(NULL, " ", &temp));
	dir = atoi(strtok_s(NULL, " ", &temp));
	txtid = TXTID_SPIKE;
	SetVolume();
	SetComponent();
}

Spike::Spike(D3DXVECTOR3 & ipos,int id,short idir)
{
	pos = ipos;
	txtid = id;
	dir = idir;
	SetVolume();	
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

VOID Spike::SetVolume()
{
	if (txtid == TXTID_SPIKE) {
		Volume = FRECT{ 0,31,0,31 };
	}
	MyPolygon temp;
	switch (dir) {
	case CToUp:
		temp.push_back(D3DXVECTOR2(16 , 0));
		temp.push_back(D3DXVECTOR2(0, 32));
		temp.push_back(D3DXVECTOR2(32, 32));
		satvolume.push_back(temp);
		break;
	case CToDown:
		temp.push_back(D3DXVECTOR2(0, 0));
		temp.push_back(D3DXVECTOR2(32,0));
		temp.push_back(D3DXVECTOR2(16, 32));
		satvolume.push_back(temp);
		break;
	case CToLeft:
		temp.push_back(D3DXVECTOR2(0, 16));
		temp.push_back(D3DXVECTOR2(32, 0));
		temp.push_back(D3DXVECTOR2(32, 32));
		satvolume.push_back(temp);
		break;
	case CToRight:
		temp.push_back(D3DXVECTOR2(0, 0));
		temp.push_back(D3DXVECTOR2(0, 32));
		temp.push_back(D3DXVECTOR2(32, 16));
		satvolume.push_back(temp);
		break;
	}
}
