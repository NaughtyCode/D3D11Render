#include "stdafx.h"

class TRender;
class TCamera;
class TD3DDevice;

TRender*     GRender                   = NULL;
TCamera*     GCamera                   = NULL;
TD3DDevice*  GDevice                   = NULL;
char*        ASCIIResourceDirectory    = "..\\Resource\\";
wchar_t*     WCHARResourceDirectory    = L"..\\Resource\\";

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

