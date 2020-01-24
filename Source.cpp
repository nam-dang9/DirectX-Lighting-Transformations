#define WIN32_LEAN_AND_MEAN
#define BITMAP_NAME "baboon.bmp"
#include "Header.h"
#include "basics.h"
long CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {

	switch (uMessage) {
	case WM_CREATE:
	{
		return 0;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, NULL);//basically saying - yeah we took care of any paint msg without any overhead
		return 0;
	}
	case WM_KEYDOWN:
		switch (wParam) {
		case 0x30:
			// 0
			// move camera
			// set move camera bool
			setCameraMove(true);
			break;
		case 0x31:
			// 1
			// mesh1
			setObj1Move(true);
			break;
		case 0x32:
			// 2
			//mesh2
			setObj2Move(true);
			break;
			// moves current selection
		case 0x57:
			// w // move up
			if (getCameraMove()) {
				moveCamera(0.0f, 1.0f, 0.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, 0.0f, 1.0f, 0.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, 0.0f, 1.0f, 0.0f);
			}
			break;
		case 0x41:
			// a // move left
			if (getCameraMove()) {
				moveCamera(-1.0f, 0.0f, 0.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, -1.0f, 0.0f, 0.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, -1.0f, 0.0f, 0.0f);
			}
			break;
		case 0x53:
			// s // move down
			if (getCameraMove()) {
				moveCamera(0.0f, -1.0f, 0.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, 0.0f, -1.0f, 0.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, 0.0f, -1.0f, 0.0f);
			}
			break;
		case 0x44:
			// d // move right
			if (getCameraMove()) {
				moveCamera(1.0f, 0.0f, 0.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, 1.0f, 0.0f, 0.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, 1.0f, 0.0f, 0.0f);
			}
			break;
		case 0x58:
			// x // zoom out
			if (getCameraMove()) {
				moveCamera(0.0f, 0.0f, 1.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, 0.0f, 0.0f, 1.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, 0.0f, 0.0f, 1.0f);
			}
			break;
		case 0x5A:
			// z // zoom in
			if (getCameraMove()) {
				moveCamera(0.0f, 0.0f, -1.0f);
			}
			else if (getObj1Move()) {
				moveObject(1, 0.0f, 0.0f, -1.0f);
			}
			else if (getObj2Move()) {
				moveObject(2, 0.0f, 0.0f, -1.0f);
			}
			break;
		case 0x51:
			// q // rotate left
			if (getCameraMove()) {
				rotateCameraY(-0.3f);
			}
			else if (getObj1Move()) {
				rotateObjectY(1, -0.3f);
			}
			else if (getObj2Move()) {
				rotateObjectY(2, -0.3f);
			}
			break;
		case 0x45:
			// e // rotate right
			if (getCameraMove()) {
				rotateCameraY(0.3f);
			}
			else if (getObj1Move()) {
				rotateObjectY(1, 0.3f);
			}
			else if (getObj2Move()) {
				rotateObjectY(2, 0.3f);
			}
			break;
		case 0x50:
			// point lighting enabled
			// p
			SetLightingPoint();
			break;
		case 0x4F:
			// directional lighting enabled
			// o
			SetLightingDirectional();
			break;
		case 0x49:
			// spot lighting enabled
			// i
			SetLightingSpot();
			break;
		case 0x55:
			// ambient lighting enabled
			// u
			SetLightingAmbient();
			break;
		case 0x46:
			// f // rotate about z axis ccw
			if (getCameraMove()) {
				rotateCameraZ(0.3f);
			}
			else if (getObj1Move()) {
				rotateObjectZ(1, 0.3f);
			}
			else if (getObj2Move()) {
				rotateObjectZ(2, 0.3f);
			}
			break;
		case 0x47:
			// g // rotate about z axis cw
			if (getCameraMove()) {
				rotateCameraZ(-0.3f);
			}
			else if (getObj1Move()) {
				rotateObjectZ(1, -0.3f);
			}
			else if (getObj2Move()) {
				rotateObjectZ(2, -0.3f);
			}
			break;
		}
		return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;

	static char strAppName[] = "First Windows App, Zen Style";

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = strAppName;

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL,
		strAppName,
		strAppName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		512, 512,
		NULL,
		NULL,
		hInstance,
		NULL);

	g_hWndMain = hWnd;//set our global window handle

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	if (FAILED(GameInit())) {
		;//initialize Game
		//SetError("Initialization Failed");
		GameShutdown();
		return E_FAIL;
	}


	while (TRUE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			GameLoop();
		}
	}
	GameShutdown();// clean up the game
	return msg.wParam;
}

int GameInit() {
	HRESULT r = 0;//return values
	LPD3DXBUFFER pD3DXMtrlBuffer;
	LPD3DXBUFFER pD3DXMtrlBuffer2;
	D3DSURFACE_DESC desc;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//COM object
	if (g_pD3D == NULL) {
		//SetError("Could not create IDirect3D9 object");
		return E_FAIL;
	}

	r = InitDirect3DDevice(g_hWndMain, 640, 480, TRUE, D3DFMT_X8R8G8B8, g_pD3D, &g_pDevice);
	if (FAILED(r)) {//FAILED is a macro that returns false if return value is a failure - safer than using value itself
		//SetError("Initialization of the device failed");
		return E_FAIL;
	}

	r = D3DXCreateFont(g_pDevice,
		32, 0, FW_BOLD, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"Arial", &font);

	r = g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	if (FAILED(r)) {
		//SetError(_T("Couldn't get backbuffer"));
	}
	pSurface->GetDesc(&desc);

	r = g_pDevice->CreateOffscreenPlainSurface(desc.Width, desc.Height, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &BitmapSurface, NULL);
	char name[] = BITMAP_NAME;
	r = LoadBitmapToSurface(name,
		&pSurface, g_pDevice);
	r = D3DXLoadSurfaceFromSurface(BitmapSurface, NULL, NULL, pSurface, NULL, NULL, D3DX_FILTER_TRIANGLE, 0);

	if (FAILED(r)) {}
		//SetError(_T("did not copy surface"));
	
	 // Load the mesh from the specified file
		if (FAILED(D3DXLoadMeshFromX("Tiger.x", D3DXMESH_SYSTEMMEM,
			g_pDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&g_pMesh)))
		{
			// If model is not in current folder, try parent folder
			if (FAILED(D3DXLoadMeshFromX("..\\Tiger.x", D3DXMESH_SYSTEMMEM,
				g_pDevice, NULL,
				&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
				&g_pMesh)))
			{
				MessageBox(NULL, "Could not find cube.x", "Meshes.exe", MB_OK);
				return E_FAIL;
			}
		}

	// Load in the objects
	if (FAILED(D3DXLoadMeshFromX(_T("teapot.x"), D3DXMESH_SYSTEMMEM,
		g_pDevice, NULL,
		&pD3DXMtrlBuffer2, NULL,
		&g_dwNumMaterials2,
		&g_pMesh2)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(_T("..\\teapot.x"), D3DXMESH_SYSTEMMEM,
			g_pDevice, NULL,
			&pD3DXMtrlBuffer2, NULL, &g_dwNumMaterials2,
			&g_pMesh2)))
		{
			MessageBox(NULL, _T("Could not find teapot.x"), _T("Meshes.exe"), MB_OK);
			return E_FAIL;
		}
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	D3DXMATERIAL* d3dxMaterials2 = (D3DXMATERIAL*)pD3DXMtrlBuffer2->GetBufferPointer();
	pMeshMaterials2 = new D3DMATERIAL9[g_dwNumMaterials2];
	pMeshTextures2 = new LPDIRECT3DTEXTURE9[g_dwNumMaterials2];

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;

		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFile(g_pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pMeshTextures[i])))
			{
				// If texture is not in current folder, try parent folder
				const TCHAR* strPrefix = TEXT("..\\");
				const int lenPrefix = lstrlen(strPrefix);
				TCHAR strTexture[MAX_PATH];
				lstrcpyn(strTexture, strPrefix, MAX_PATH);
				lstrcpyn(strTexture + lenPrefix, d3dxMaterials[i].pTextureFilename, MAX_PATH - lenPrefix);
				// If texture is not in current folder, try parent folder
				if (FAILED(D3DXCreateTextureFromFile(g_pDevice,
					strTexture,
					&pMeshTextures[i])))
				{
					MessageBox(NULL, _T("Could not find texture map"), _T("Meshes.exe"), MB_OK);
				}
			}
		}
	}

	g_pMesh->CloneMeshFVF(D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, g_pDevice, &g_pMesh);


	if (FAILED(D3DXComputeNormals(g_pMesh, NULL))) {
		return E_FAIL;
	}
	for (DWORD i = 0; i < g_dwNumMaterials2; i++)
	{
		// Copy the material
		pMeshMaterials2[i] = d3dxMaterials2[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		pMeshMaterials2[i].Ambient = pMeshMaterials2[i].Diffuse;

		pMeshTextures2[i] = NULL;
		if (d3dxMaterials2[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials2[i].pTextureFilename) > 0)
		{
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFile(g_pDevice,
				d3dxMaterials2[i].pTextureFilename,
				&pMeshTextures2[i])))
			{
				// If texture is not in current folder, try parent folder
				const TCHAR* strPrefix = TEXT("..\\");
				const int lenPrefix = lstrlen(strPrefix);
				TCHAR strTexture[MAX_PATH];
				lstrcpyn(strTexture, strPrefix, MAX_PATH);
				lstrcpyn(strTexture + lenPrefix, d3dxMaterials2[i].pTextureFilename, MAX_PATH - lenPrefix);
				// If texture is not in current folder, try parent folder
				if (FAILED(D3DXCreateTextureFromFile(g_pDevice,
					strTexture,
					&pMeshTextures2[i])))
				{
					MessageBox(NULL, _T("Could not find texture map"), _T("Meshes.exe"), MB_OK);
				}
			}
		}
	}
	SetupMatrices();
	D3DXMatrixTranslation(&matObj1, -2, 0, 0);
	D3DXMatrixTranslation(&matObj2, 1, 0, 0);

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();
	g_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	return S_OK;
}
void PrintText() {
	font->DrawText(NULL,
		fpsText.c_str(),
		-1, &rect,
		DT_RIGHT | DT_TOP,
		0XFFFFFFFF);
}
int GameLoop() {
	LARGE_INTEGER startTime, endTime, freq, frameTime;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startTime);

	Render();

	QueryPerformanceCounter(&endTime);
	frameTime.QuadPart = endTime.QuadPart - startTime.QuadPart;

	frameTime.QuadPart *= 1000;
	frameTime.QuadPart /= freq.QuadPart;

	fpsTime.QuadPart += frameTime.QuadPart;
	fpsFrames++;

	if (fpsTime.QuadPart >= 500) {
		fpsText = std::to_string(fpsFrames * 2);
		fpsFrames = 0;
		fpsTime.QuadPart -= 500;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
		PostQuitMessage(0);
	return S_OK;
}

int GameShutdown() {
	if (pSurface) {
		pSurface->Release();
		pSurface = 0;
	}
	if (font)
	{
		font->Release();
	}
	//release resources. First display adapter because COM object created it, then COM object
	if (g_pDevice)
		g_pDevice->Release();

	if (g_pD3D)
		g_pD3D->Release();

	return S_OK;
}

int Render() {
	HRESULT r;
	LPDIRECT3DSURFACE9 pBackSurf = 0;
	if (!g_pDevice) {
		//	SetError("Cannot render because there is no device");
		return E_FAIL;
	}

	//clear the display arera with colour black, ignore stencil buffer
	g_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 25), 1.0f, 0);
	
	//get pointer to backbuffer
	r = g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(r)) {
		//SetError("Couldn't get backbuffer");
	}


	if (FAILED(r)) {
		//	SetError("could not load bitmap surface");
	}

	r = g_pDevice->UpdateSurface(pSurface, NULL, pBackSurf, NULL);
	if (FAILED(r)) {
		//	SetError("did not copy surface");
	}

	g_pDevice->BeginScene();
	g_pDevice->SetTransform(D3DTS_WORLD, &matObj1);
	// Meshes are divided into subsets, one for each material. Render them in
	// a loop
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Set the material and texture for this subset
		g_pDevice->SetMaterial(&pMeshMaterials[i]);
		g_pDevice->SetTexture(0, pMeshTextures[i]);

		// Draw the mesh subset
		g_pMesh->DrawSubset(i);
	}
	g_pDevice->SetTransform(D3DTS_WORLD, &matObj2);
	for (DWORD i = 0; i < g_dwNumMaterials2; i++)
	{
		// Set the material and texture for this subset
		g_pDevice->SetMaterial(&pMeshMaterials2[i]);
		g_pDevice->SetTexture(0, pMeshTextures2[i]);

		// Draw the mesh subset
		g_pMesh2->DrawSubset(i);
	}
	PrintText();
	g_pDevice->EndScene();

	pBackSurf->Release();//release lock

	pBackSurf = 0;
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);
	g_pDevice->Present(NULL, NULL, NULL, NULL);//swap over buffer to primary surface
	return S_OK;
}
VOID SetupMatrices()
{
	// For our world matrix, we will just leave it as the identity
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, 50.0f);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld); // Takes whatever is in the matrix, and sets it to the world
			// ** This is how we will move objects and rotate later **

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -10.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 500.0f);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

int LoadBitmapToSurface(char* PathName, LPDIRECT3DSURFACE9* ppSurface, LPDIRECT3DDEVICE9 pDevice) {
	HRESULT r;
	HBITMAP hBitmap;
	BITMAP Bitmap;

	hBitmap = (HBITMAP)LoadImage(NULL, PathName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL) {
		//	SetError("Unable to load bitmap");
		return E_FAIL;
	}

	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	DeleteObject(hBitmap);//we only needed it for the header info to create a D3D surface

	//create surface for bitmap
	r = pDevice->CreateOffscreenPlainSurface(d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, ppSurface, NULL);

	if (FAILED(r)) {
		//	SetError("Unable to create surface for bitmap load");
		return E_FAIL;
	}
	//load bitmap onto surface
	r = D3DXLoadSurfaceFromFile(*ppSurface, NULL, NULL, PathName, NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(r)) {
		//SetError("Unable to laod file to surface");
		return E_FAIL;
	}

	return S_OK;
}

/*
	Move the camera based on x, y, z
*/
void moveCamera(float x, float y, float z) {
	D3DXMATRIX newM;
	D3DXMatrixTranslation(&newM, x, y, z);
	D3DXMatrixMultiply(&matView, &matView, &newM);
}
/*
	Rotate the camera about x.
*/
void rotateCameraX(float r) {
	// rotate around y
	D3DXMATRIX newM;
	D3DXMatrixRotationX(&newM, r);
	D3DXMatrixMultiply(&matView, &matView, &newM);
}
/*
	Rotate the camera about y.
*/
void rotateCameraY(float r) {
	// rotate around y
	D3DXMATRIX newM;
	D3DXMatrixRotationY(&newM, r);
	D3DXMatrixMultiply(&matView, &matView, &newM);
}
/*
	Rotate the camera about z.
*/
void rotateCameraZ(float r) {
	// rotate around y
	D3DXMATRIX newM;
	D3DXMatrixRotationZ(&newM, r);
	D3DXMatrixMultiply(&matView, &matView, &newM);
}
/*
	Move the object based on the object number and x, y, z.
*/
void moveObject(int objNum, float x, float y, float z) {
	D3DXMATRIX newM;
	if (objNum == 1) {
		D3DXMatrixTranslation(&newM, x, y, z);
		D3DXMatrixMultiply(&matObj1, &matObj1, &newM);
	}
	else {
		D3DXMatrixTranslation(&newM, x, y, z);
		D3DXMatrixMultiply(&matObj2, &matObj2, &newM);
	}
}
/*
	Rotate the object about x.
*/
void rotateObjectX(int objNum, float r) {
	// rotate around y
	D3DXMATRIX newM, matRot, backM;
	float x, y, z;
	if (objNum == 1) {
		D3DXMatrixRotationX(&matRot, r);
		x = matObj1._41;
		y = matObj1._42;
		z = matObj1._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);
		D3DXMatrixMultiply(&newM, &newM, &matRot);
		D3DXMatrixTranslation(&backM, x, y, z);
		D3DXMatrixMultiply(&newM, &newM, &backM);
		D3DXMatrixMultiply(&matObj1, &matObj1, &newM);
	}
	else {
		x = matObj2._41;
		y = matObj2._42;
		z = matObj2._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);

		D3DXMatrixRotationX(&matRot, r);

		D3DXMatrixMultiply(&newM, &newM, &matRot);

		D3DXMatrixTranslation(&backM, x, y, z);

		D3DXMatrixMultiply(&newM, &newM, &backM);

		D3DXMatrixMultiply(&matObj2, &matObj2, &newM);
	}
}
/*
	Rotate the camera about y.
*/
void rotateObjectY(int objNum, float r) {
	// rotate around y
	D3DXMATRIX newM, matRot, backM;
	float x, y, z;
	if (objNum == 1) {
		D3DXMatrixRotationY(&matRot, r);
		x = matObj1._41;
		y = matObj1._42;
		z = matObj1._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);
		D3DXMatrixMultiply(&newM, &newM, &matRot);
		D3DXMatrixTranslation(&backM, x, y, z);
		D3DXMatrixMultiply(&newM, &newM, &backM);
		D3DXMatrixMultiply(&matObj1, &matObj1, &newM);
	}
	else {
		x = matObj2._41;
		y = matObj2._42;
		z = matObj2._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);

		D3DXMatrixRotationY(&matRot, r);

		D3DXMatrixMultiply(&newM, &newM, &matRot);

		D3DXMatrixTranslation(&backM, x, y, z);

		D3DXMatrixMultiply(&newM, &newM, &backM);

		D3DXMatrixMultiply(&matObj2, &matObj2, &newM);
	}
}
/*
	Rotate the camera about z.
*/
void rotateObjectZ(int objNum, float r) {
	// rotate around y
	D3DXMATRIX newM, matRot, backM;
	float x, y, z;
	if (objNum == 1) {
		D3DXMatrixRotationZ(&matRot, r);
		x = matObj1._41;
		y = matObj1._42;
		z = matObj1._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);
		D3DXMatrixMultiply(&newM, &newM, &matRot);
		D3DXMatrixTranslation(&backM, x, y, z);
		D3DXMatrixMultiply(&newM, &newM, &backM);
		D3DXMatrixMultiply(&matObj1, &matObj1, &newM);
	}
	else {
		x = matObj2._41;
		y = matObj2._42;
		z = matObj2._43;
		D3DXMatrixTranslation(&newM, -x, -y, -z);
		D3DXMatrixRotationZ(&matRot, r);
		D3DXMatrixMultiply(&newM, &newM, &matRot);
		D3DXMatrixTranslation(&backM, x, y, z);
		D3DXMatrixMultiply(&newM, &newM, &backM);
		D3DXMatrixMultiply(&matObj2, &matObj2, &newM);
	}
}

bool getCameraMove() {
	return CameraMove;
}

bool getObj1Move() {
	return Obj1Move;
}

bool getObj2Move() {
	return Obj2Move;
}
/*
	Set to camera
*/
void setCameraMove(bool b) {
	CameraMove = b;
	Obj1Move = false;
	Obj2Move = false;
}
/*
	Set to 1st Mesh
*/
void setObj1Move(bool b) {
	Obj1Move = b;
	CameraMove = false;
	Obj2Move = false;
}
/*
	Set to 2nd Mesh
*/
void setObj2Move(bool b) {
	Obj2Move = b;
	CameraMove = false;
	Obj1Move = false;
}
/*
	Set Directional Lighting
*/
void SetLightingDirectional() {
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;

	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 vecDir;
	vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	g_pDevice->SetMaterial(&material);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, TRUE);
	g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(10, 10, 10));
}
/*
	Set Ambient Lighting
*/
void SetLightingAmbient() {
	g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
}
/*
	Set Spot Lighting
*/
void SetLightingSpot() {
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;

	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_SPOT;
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Position = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	light.Range = 100.0f;   
	light.Attenuation0 = 0.0f;   
	light.Attenuation1 = 0.125f;    
	light.Attenuation2 = 0.0f;    
	light.Phi = D3DXToRadian(40.0f);
	light.Theta = D3DXToRadian(20.0f);
	light.Falloff = 1.0f;

	g_pDevice->SetMaterial(&material);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, TRUE);
	g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(10, 10, 10));
}
/*
	Set Point Lighting
*/
void SetLightingPoint() {
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_POINT;
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	light.Position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	light.Range = 100.0f;
	light.Attenuation0 = 0.0f;
	light.Attenuation1 = 0.125f;
	light.Attenuation2 = 0.0f;

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_pDevice->SetMaterial(&material);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, TRUE);
	g_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(10, 10, 10));
}