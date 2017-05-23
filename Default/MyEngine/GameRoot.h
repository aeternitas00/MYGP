#pragma once

#include "stdafx.h"
class SystemManager;
class RenderManager;
class SoundManager;

class GameRoot {
private:
	SystemManager*			pSysM;
	RenderManager*			pRdrM;
	SoundManager*			pSndM;
	WNDCLASSEX				wc;
	HWND					hWnd;
	static GameRoot*		instance;
	
	GameRoot();
	HRESULT Initialize();
	//static VOID Cleanup();

public:
	~GameRoot();
	static GameRoot* GetInstance();


	INT Main();
	inline HWND* GetHwnd() { return &hWnd; }
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
