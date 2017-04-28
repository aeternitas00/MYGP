#pragma once

#include "stdafx.h"
class SoundManager;
class SystemManager;
class RenderManager;

class GameRoot {
private:
	SoundManager*			pSndM;
	SystemManager*			pSysM;
	RenderManager*			pRdrM;

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
	inline HWND* get_hwnd() { return &hWnd; }
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
