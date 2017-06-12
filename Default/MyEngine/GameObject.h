#pragma once
#include "stdafx.h"
#include <list>
using namespace std;
class ComponentBase;
class GraphicsComponent;
class PhysicsComponent;

typedef std::list<D3DXVECTOR2> MyPolygon;

class GameObject
{
public:
	D3DXVECTOR3 pos;
	float angle;
	int txtid;
protected:
	std::list<ComponentBase*> ComponentList;
	FRECT Volume;
	std::list<MyPolygon> satvolume;
public:
	GameObject();
	GameObject(D3DXVECTOR3& ipos, int id);
	VOID SetTxt(const int id);
	~GameObject();

	bool IsInScreen() { return pos.x<MAX_X+100&&pos.x>-200 && pos.y<MAX_Y+100&&pos.y>-200 ? true : false; }
	RESULT Update();
	virtual RENDERSQUARE GetRenderSquare();
	virtual RESULT UpdateSub();
	virtual short GetDir() { return 0; }

	FRECT GetVolume() { return Volume; }
	std::list<MyPolygon> GetSATVolume() { return satvolume; }

	VOID PushBackSATVolume(MyPolygon& input) { satvolume.push_back(input); }
	int GetSATLength() { return satvolume.size(); }
	VOID UpdateByMovingScene(int side);
	virtual VOID SetComponent();
	virtual VOID AddComponent(ComponentBase* pcmp) { ComponentList.push_back(pcmp); }
};

