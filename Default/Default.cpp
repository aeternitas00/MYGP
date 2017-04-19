// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

// define the screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// define the keyboard macro
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
LPD3DXMESH meshTeapot;
POINT MousePos;    // mouse position

				   // function prototypes
void initD3D(HWND hWnd);
void render_frame(void);
void cleanD3D(void);
void init_graphics(void);
void init_light(void);

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Game Input Program",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);

	// enter the main loop:

	MSG msg;

	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		render_frame();

		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	init_graphics();
	init_light();

	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	d3ddev->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);    // anisotropic level
	d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);    // minification
	d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);    // magnification
	d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);    // mipmap
}


// this is the function used to render a single frame
void render_frame(void)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();

	// set the view transform
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 2.0f, 6.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),      // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction
	d3ddev->SetTransform(D3DTS_VIEW, &matView);

	// set the projection transform
	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane
	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);

	static float index = 0.0f; // index+=0.03f;

							   // collect keyboard data
	if (KEY_DOWN(VK_LEFT)) index += 0.03f;
	if (KEY_DOWN(VK_RIGHT)) index -= 0.03f;

	// collect mouse data
	GetCursorPos(&MousePos);    // get the mouse data
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);    // move the mouse to the center
	MousePos.x -= SCREEN_WIDTH / 2;
	MousePos.y -= SCREEN_HEIGHT / 2;
	index += MousePos.x * 0.01f;

	// set the world transform
	D3DXMATRIX matRotateY;
	D3DXMatrixRotationY(&matRotateY, index);
	d3ddev->SetTransform(D3DTS_WORLD, &(matRotateY));

	// draw the teapot
	meshTeapot->DrawSubset(0);

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	meshTeapot->Release();
	d3ddev->Release();
	d3d->Release();
}


// this is the function that puts the 3D models into video RAM
void init_graphics(void)
{
	D3DXCreateTeapot(d3ddev, &meshTeapot, NULL);    // create the teapot
}


// this is the function that sets up the lights and materials
void init_light(void)
{
	D3DLIGHT9 light;    // create the light struct
	D3DMATERIAL9 material;    // create the material struct

	ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
	light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	light.Direction = D3DXVECTOR3(-1.0f, -0.3f, -1.0f);

	d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
	d3ddev->LightEnable(0, TRUE);    // turn on light #0

	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}
