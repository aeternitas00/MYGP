// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Main.h"

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE,LPWSTR,int)
{
	//INT WINAPI Main(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
	UNREFERENCED_PARAMETER(hInstance);
	GameManager::GetInstance()->Main();
	return 0;
}