#include "stdafx.h"
#include "TD3D11Render.h"
#include "TCamera.h"


TD3D11Render::TD3D11Render():
	TargetSurface(0),
	CurrentViewPort(0)
{
	
}

TD3D11Render::~TD3D11Render()
{
}

int TD3D11Render::CreateRender(HWND hWnd)
{
	TargetSurface = new TRenderTarget();
	CurrentViewPort = new TViewPort();
	return 1;
}

void TD3D11Render::StartFrame()
{
	TargetSurface->Clear();
}

void TD3D11Render::EndFrame()
{
	GDevice->Present();
}

void TD3D11Render::Release()
{
	SAFE_RELEASEDELETE(TargetSurface);
}
