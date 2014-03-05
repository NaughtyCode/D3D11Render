#include "stdafx.h"
#include "TRender.h"

TRender::TRender():
	RenderTarget(0),
	ViewPort(0), 
	Resource(0)
{
	
}

TRender::~TRender()
{
}

int TRender::CreateRender(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd,&rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	
	RenderTarget = new TRenderTarget();
	assert(RenderTarget);
	RenderTarget->CreateRenderTarget();
	ViewPort = new TViewPort();
	assert(ViewPort);
	ViewPort->CreateViewPort();
	Resource = new TResource();
	assert(Resource);
	Resource->CreateResource();
	return 1;
}

void TRender::RenderFrame()
{
	RenderTarget->Clear();
	Resource->PostResource();
	GDevice->Present();
}

void TRender::Release()
{
	SAFE_DELETERELEASE(RenderTarget);
	SAFE_DELETERELEASE(Resource);
}
