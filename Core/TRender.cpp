#include "stdafx.h"
#include "TRender.h"

const WCHAR* vsfile = L"..\\Resource\\shaders\\primitivevsshader.hlsl";
const WCHAR* psfile = L"..\\Resource\\shaders\\primitivepsshader.hlsl";

TRender::TRender() :Device(0), RenderTarget(0), ViewPort(0), Resource(0)
{
}

TRender::~TRender()
{

}

int TRender::CreateRender(HWND hWnd)
{
	Device = new TD3DDevice(hWnd);
	assert(Device);
	int rt;
	rt=Device->CreateDevice();
	assert(rt);
	RenderTarget = new TRenderTarget(Device);
	assert(RenderTarget);
	RenderTarget->CreateRenderTarget();
	ViewPort = new TViewPort(Device);
	assert(RenderTarget);
	ViewPort->CreateViewPort();
	Resource = new TResource(Device);
	assert(Resource);
	Resource->CreateResource(vsfile,psfile);
	return 1;
}

void TRender::RenderFrame()
{
	RenderTarget->Clear();
	Resource->PostResource();
	Device->GetSwapChain()->Present(0,0);
}

void TRender::Release()
{

}
