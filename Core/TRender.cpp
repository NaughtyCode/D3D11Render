#include "stdafx.h"
#include "TRender.h"
#include "Core.h"

extern TRender* GRender;

TRender::TRender() :Device(0), 
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

	Device = new TD3DDevice(hWnd);
	assert(Device);
	int rt;
	rt=Device->CreateDevice();
	assert(rt);
	
	RenderTarget = new TRenderTarget(Device);
	assert(RenderTarget);
	RenderTarget->CreateRenderTarget();
	ViewPort = new TViewPort(Device);
	assert(ViewPort);
	ViewPort->CreateViewPort();
	Resource = new TResource(Device);
	assert(Resource);
	Resource->CreateResource();
	return 1;
}

void TRender::RenderFrame()
{
	RenderTarget->Clear();
	Resource->PostResource();
	Device->Present();
}

void TRender::Release()
{
	SAFE_DELETERELEASE(RenderTarget);
	SAFE_DELETERELEASE(Resource);
	SAFE_DELETERELEASE(Device);
}
