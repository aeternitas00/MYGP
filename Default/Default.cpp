/**-----------------------------------------------------------------------------
* \brief 인덱스버퍼 생성
* 파일: IndexBuffer.cpp
*
* 설명: 인덱스 버퍼(Index Buffer)란 정점을 보관하기 위한 정점버퍼(VB)처럼
*       인덱스를 보관하기위한 전용 객체이다. D3D 학습예제에는 이러한 예제가
*       IB를 사용한 예제가 없기 때문에 새롭게 추가한 것이다.
*------------------------------------------------------------------------------
*/

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 1000

LPDIRECT3D9             g_pD3D = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9	g_pIB = NULL; 

struct CUSTOMVERTEX
{
	FLOAT x, y, z;	
	DWORD color;	
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

struct MYINDEX
{
	WORD	_0, _1, _2;		
};

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	/// 디바이스 생성
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	/// 컬링기능을 끈다.
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	/// Z버퍼기능을 켠다.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	/// 정점에 색깔값이 있으므로, 광원기능을 끈다.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}


HRESULT InitVBnIB()
{
	char str[MAX_SIZE];
	ifstream inFile("Input.txt");
	inFile.getline(str, MAX_SIZE);
	// Firstline : num of vb , ib
	int vbl = atoi(strtok(str, " "));
	int ibl = atoi(strtok(NULL, " "));
	strtok(NULL, " ");

	CUSTOMVERTEX *vertices = new CUSTOMVERTEX[vbl];
	MYINDEX*	indices=new MYINDEX[ibl];

	for (int n =0; n<vbl;n++) {
		inFile.getline(str, MAX_SIZE);
		vertices[n].color=0xffffffff;
		vertices[n].x= atoi(strtok(str, " "));
		vertices[n].y = atoi(strtok(NULL, " "));
		vertices[n].z = atoi(strtok(NULL, " "));
		strtok(NULL, " ");
	}

	for (int n = 0; n<ibl; n++) {
		inFile.getline(str, MAX_SIZE);
		indices[n]._0 = atoi(strtok(str, " "));
		indices[n]._1 = atoi(strtok(NULL, " "));
		indices[n]._2 = atoi(strtok(NULL, " "));
		strtok(NULL, " ");
	}

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(vbl * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	/// 정점버퍼를 값으로 채운다. 
	/// 정점버퍼의 Lock()함수를 호출하여 포인터를 얻어온다.
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, vbl * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, vertices, vbl * sizeof(CUSTOMVERTEX));
	g_pVB->Unlock();

	if (FAILED(g_pd3dDevice->CreateIndexBuffer(ibl * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	/// 인덱스버퍼를 값으로 채운다. 
	/// 인덱스버퍼의 Lock()함수를 호출하여 포인터를 얻어온다.
	VOID* pIndices;
	if (FAILED(g_pIB->Lock(0, ibl * sizeof(MYINDEX), (void**)&pIndices, 0)))
		return E_FAIL;
	memcpy(pIndices, indices, ibl * sizeof(MYINDEX));
	g_pIB->Unlock();

	delete vertices;
	delete indices;

	return S_OK;
}

/**-----------------------------------------------------------------------------
* 행렬 설정
*------------------------------------------------------------------------------
*/
VOID SetupMatrices()
{
	/// 월드행렬
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);							/// 월드행렬을 단위행렬으로 설정
	D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f);	/// Y축을 중심으로 회전행렬 생성
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);		/// 디바이스에 월드행렬 설정

															/// 뷰행렬을 설정
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	/// 프로젝션 행렬 설정
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}



/**-----------------------------------------------------------------------------
* 초기화 객체들 소거
*------------------------------------------------------------------------------
*/
VOID Cleanup()
{
	if (g_pIB != NULL)
		g_pIB->Release();

	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}




/**-----------------------------------------------------------------------------
* 화면 그리기
*------------------------------------------------------------------------------
*/
VOID Render()
{
	/// 후면버퍼와 Z버퍼 초기화
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// 행렬설정
	SetupMatrices();

	/// 렌더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		/// 정점버퍼의 삼각형을 그린다.
		/// 1. 정점정보가 담겨있는 정점버퍼를 출력 스트림으로 할당한다.
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		/// 2. D3D에게 정점쉐이더 정보를 지정한다. 대부분의 경우에는 FVF만 지정한다.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		/// 3. 인덱스버퍼를 지정한다.
		g_pd3dDevice->SetIndices(g_pIB);
		/// 4. DrawIndexedPrimitive()를 호출한다.
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		/// 렌더링 종료
		g_pd3dDevice->EndScene();
	}

	/// 후면버퍼를 보이는 화면으로!
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




/**-----------------------------------------------------------------------------
* 윈도우 프로시져
*------------------------------------------------------------------------------
*/
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




/**-----------------------------------------------------------------------------
* 프로그램 시작점
*------------------------------------------------------------------------------
*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	/// 윈도우 클래스 등록
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL };
	RegisterClassEx(&wc);

	/// 윈도우 생성
	HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 07: IndexBuffer",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	/// Direct3D 초기화
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		/// 정점버퍼 초기화
		if (SUCCEEDED(InitVBnIB()))
		{
		/// 인덱스버퍼 초기화
			/// 윈도우 출력
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);
							/// 메시지 루프
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				/// 메시지큐에 메시지가 있으면 메시지 처리
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					/// 처리할 메시지가 없으면 Render()함수 호출
					Render();
			}
		}
	}

	/// 등록된 클래스 소거
	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	return 0;
}

