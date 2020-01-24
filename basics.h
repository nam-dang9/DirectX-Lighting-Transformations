#pragma once
//put all include files here
#include "Header.h"
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#define DRVERTEX_FLAGS (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

/*Forward Declarations*/
int GameInit();
int GameLoop();
int GameShutdown();
void SetError(char*, ...);
void SetupMatrices();
void moveCamera(float, float, float);
void rotateCameraX(float);
void rotateCameraY(float);
void rotateCameraZ(float);
void moveObject(int, float, float, float);
void rotateObjectX(int, float);
void rotateObjectY(int, float);
void rotateObjectZ(int, float);
bool getCameraMove();
bool getObj1Move();
bool getObj2Move();
void setCameraMove(bool);
void setObj1Move(bool);
void setObj2Move(bool);
void SetLightingDirectional();
void SetLightingAmbient();
void SetLightingSpot();
void SetLightingPoint();
HRESULT RestoreGraphics();

int Render();
int LoadBitmapToSurface(char*, LPDIRECT3DSURFACE9*, LPDIRECT3DDEVICE9);
void SimpleBitmapDraw(char*, LPDIRECT3DSURFACE9, int, int);
//using namespace DirectX::SimpleMath;
//int InitDirect3DDevice(HWND, int, int, BOOL, D3DFORMAT, LPDIRECT3D8, LPDIRECT3DDEVICE8*);

/************GLOBALS*****************************/
LPDIRECT3D9 g_pD3D = 0;//COM object
LPDIRECT3DDEVICE9 g_pDevice = 0;//graphics device
HWND g_hWndMain;//handle to main window
LPD3DXFONT font;
int fpsFrames;
LARGE_INTEGER fpsTime;
PDIRECT3DSURFACE9 BitmapSurface = 0;
DWORD                   g_dwNumMaterials = 0L;   // Number of mesh materials
DWORD                   g_dwNumMaterials2 = 0L;   // Number of mesh materials
LPD3DXMESH              g_pMesh = NULL; // Our mesh object in sysmem
LPD3DXMESH              g_pMesh2 = NULL; // Our mesh object in sysmem
D3DMATERIAL9* pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
D3DMATERIAL9* pMeshMaterials2 = NULL;
LPDIRECT3DTEXTURE9* pMeshTextures2 = NULL;
D3DXMATRIX matView;
D3DXMATRIX matObj1;
D3DXMATRIX matObj2;
D3DMATERIAL9 material;
D3DLIGHT9 light;
bool CameraMove = true; 
bool Obj1Move = false;
bool Obj2Move = false;
LPDIRECT3DSURFACE9 pSurface = 0;
D3DPRESENT_PARAMETERS d3dpp;
std::string fpsText;
RECT rect;
/***********************************************/
int InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice) {
	//rendering info
	D3DDISPLAYMODE d3ddm;//current display mode info
	HRESULT r = 0;

	if (*ppDevice)
		(*ppDevice)->Release();

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	r = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(r)) {
		//SetError("Could not get display adapter information");
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = bWindowed ? Width : d3ddm.Width;
	d3dpp.BackBufferHeight = bWindowed ? Height : d3ddm.Height;
	d3dpp.BackBufferFormat = bWindowed ? d3ddm.Format : FullScreenFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hWndTarget;
	d3dpp.Windowed = bWindowed;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = 0;//default refresh rate
	d3dpp.PresentationInterval = bWindowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	rect = { 0, 30, (LONG)d3dpp.BackBufferWidth - 20, 300 };
	r = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
	if (FAILED(r)) {
		//SetError("Could not create the render device");
		return E_FAIL;
	}
	g_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//	g_DeviceHeight = Height;
	//	g_DeviceWidth = Width;

	//	g_SavedPresParams = d3dpp;
	return S_OK;
}

void SetError(char* szFormat, ...) {
	char szBuffer[1024];
	va_list pArgList;
	va_start(pArgList, szFormat);

	//_vsntprintf(szBuffer, sizeof(szBuffer)/sizeof(char), szFormat, pArgList);

	va_end(pArgList);

	OutputDebugString(szBuffer);
	OutputDebugString("\n");
	printf("error!!");
}

