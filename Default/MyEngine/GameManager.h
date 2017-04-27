#pragma once

#include "stdafx.h"
class SoundManager;
class SystemManager;
class RenderManager;

class GameManager {
private:
	SoundManager*			pSndM;
	SystemManager*			pSysM;
	RenderManager*			pRdrM;

	WNDCLASSEX				wc;
	HWND					hWnd;
	static GameManager*		instance;
	
	GameManager();
	HRESULT Initialize();
	//static VOID Cleanup();

public:
	~GameManager();
	static GameManager* GetInstance();

	
	INT Main();
	inline HWND* get_hwnd() { return &hWnd; }
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
