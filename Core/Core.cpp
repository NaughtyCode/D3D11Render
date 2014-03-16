#include "stdafx.h"

class TD3D11Render;
class TCamera;
class TDevice;

TResource*    GResource                 = 0;
TD3D11Render* GRender                   = 0;
TCamera*      GCamera                   = 0;
TDevice*      GDevice                   = 0;
DWORD         GGPUFrameTime             = 0;
char*         ASCIIResourceDirectory    = "..\\Resource\\";
wchar_t*      WCHARResourceDirectory    = L"..\\Resource\\";

void CreateRender(HWND hWnd)
{
	int rt;
	assert(!GCamera);
	GCamera = new TCamera(hWnd);
	assert(GCamera);
	
	assert(!GDevice);
	GDevice = new TDevice(hWnd);
	assert(GDevice);
	rt=GDevice->CreateDevice();
	assert(rt);
	
	assert(!GRender);
	GRender = new TD3D11Render();
	GRender->CreateRender(hWnd);
	assert(GRender);
}

void DestroyRender()
{
	SAFE_RELEASEDELETE(GCamera);
	SAFE_RELEASEDELETE(GDevice);
	SAFE_RELEASEDELETE(GRender);
}

void GetResourceDirASCII(std::string& FileName)
{
	std::string root(ASCIIResourceDirectory);
	FileName=root+FileName;
}

void GetResourceDirWCHAR(std::wstring& FileName)
{
	std::wstring root(WCHARResourceDirectory);
	FileName=root+FileName;
}

void GDrawFrame()
{
	GStartFrame();
	if(!GResource)
	{
		GResource = new TResource();
		GResource->CreateResource();
	}
	GResource->PostResource();
	
	GEndFrame();
}

void GStartFrame()
{
	GRender->StartFrame();
}

void GEndFrame()
{
	GRender->EndFrame();
}
