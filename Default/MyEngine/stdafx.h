// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <d3d9.h>
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <Winuser.h>
#include <strsafe.h>
#include "GameRoot.h"
#include "GameMovableObject.h"
#include "RenderManager.h"
#include "SystemManager.h"
#include "GameObject.h"
#include "ComponentBase.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <list>