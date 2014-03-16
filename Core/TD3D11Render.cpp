#include "stdafx.h"
#include "TD3D11Render.h"
#include "TCamera.h"


TD3D11Render::TD3D11Render():
	RenderTarget(0),
	CurrentViewPort(0)
{
	
}

TD3D11Render::~TD3D11Render()
{
}

int TD3D11Render::CreateRender(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd,&rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	
	RenderTarget = new TRenderTarget();
	assert(RenderTarget);
	RenderTarget->CreateRenderTarget();
	CurrentViewPort = new TViewPort();
	assert(CurrentViewPort);
	CurrentViewPort->CreateViewPort();
	
	return 1;
}

void TD3D11Render::StartFrame()
{
	RenderTarget->Clear();
}

void TD3D11Render::EndFrame()
{
	GDevice->Present();
}

void TD3D11Render::Release()
{
	SAFE_RELEASEDELETE(RenderTarget);
}
