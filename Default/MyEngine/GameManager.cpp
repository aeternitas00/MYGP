#include "stdafx.h"

GameManager*		GameManager::instance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager() {
	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	delete instance;
}

//VOID GameManager::Cleanup()
//{
//
//}

GameManager * GameManager::GetInstance()
{
	if (instance == NULL) {
		instance = new GameManager();
	}
	return instance;
}

HRESULT GameManager::Initialize() {
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,L"Test Engine", NULL };
	RegisterClassEx(&wc);
	hWnd = CreateWindow(L"Test Engine", L"Test Engine",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	pRdrM = RenderManager::GetInstance();
	if (pRdrM == nullptr) { MessageBox(NULL, L"Render Initialize Failed", L"MyEngine.exe", MB_OK);  return E_FAIL; }
	return S_OK;
}

LRESULT GameManager::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		/*Cleanup();*/
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT GameManager::Main()
{
	if(FAILED(Initialize()))return -1;
	
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	// Enter the message loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			pRdrM->Render();
		}
	}

	return 0;
}

