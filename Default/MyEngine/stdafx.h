// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <typeinfo>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#define MAX_X 654
#define MAX_Y 512

enum RESULT {
	Default,
	Destroy,
	OutOfScreen,
};
typedef struct __MYRECT {
	unsigned int x, y;
}MYRECT;

typedef struct __floatrect {
	float top, bottom, left, right;
}FRECT;



#include <map>
#include <d3d9.h>
#include <Windows.h>
#include <mmsystem.h>
#include <functional>
#include <d3dx9.h>
#include <Winuser.h>
#include <strsafe.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include "GameRoot.h"
#include "Factory.h"
#include "ListClass.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "SystemManager.h"
#include "EnemyBullet.h"
#include "GameObject.h"
#include "GameMovableObject.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Spike.h"
#include "MissileLauncher.h"
#include "ComponentBase.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "ObjectShake.h"
#include "ParticlePhysicsComponent.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerInputComponent.h"
#include "GameStaticObject.h"
#include "PlayerBulletPhysicsComponent.h"
#include "Particle.h"
#include "TerrainGraphicsComponent.h"
#include "ParticleGraphicsComponent.h"
#include "GameTerrain.h"
#include "SavePoint.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "PlayerPhysicsComponent.h"
#include "EnemyBulletPhysicsComponent.h"
#include "IntroScript.h"
#include "IntroCharacter.h"


#pragma comment(lib,"d3dx9.lib")  
#pragma comment(lib,"d3d9.lib")  


template <class T> void constructor(ListBase* as, char* n)
{
	static_cast<ListChild<T*>*>(as)->add(new T(), n);
}