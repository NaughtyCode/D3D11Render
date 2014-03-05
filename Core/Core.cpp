#include "stdafx.h"

class TRender;
class TCamera;
class TD3DDevice;

TRender*    GRender         = NULL;
TCamera*    GCamera         = NULL;
TD3DDevice* GDevice         = NULL;
char*       ResourceRoot    = "..\\Resources\\";

void CreateRender(HWND hWnd)
{
	int rt;
	assert(!GCamera);
	GCamera = new TCamera(hWnd);
	assert(GCamera);
	
	assert(!GDevice);
	GDevice = new TD3DDevice(hWnd);
	assert(GDevice);
	rt=GDevice->CreateDevice();
	assert(rt);
	
	assert(!GRender);
	GRender = new TRender();
	GRender->CreateRender(hWnd);
	assert(GRender);
}

void DestroyRender()
{
	SAFE_DELETERELEASE(GCamera);
	SAFE_DELETERELEASE(GDevice);
	SAFE_DELETERELEASE(GRender);
}

