#include "stdafx.h"
#include "TViewPort.h"


TViewPort::TViewPort(TD3DDevice* device) :Device(device)
{
}

TViewPort::~TViewPort()
{
}

int TViewPort::CreateViewPort()
{
	UINT width;
	UINT height;
	RECT rect;

	HWND hWnd = Device->GetWindowHandle();

	if (GetWindowRect(hWnd, &rect)){
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
	else{
		width = 900;
		height = 600;
	}

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	Device->GetImmediateContext()->RSSetViewports(1, &vp);
	return 1;
}

void TViewPort::Release()
{

}
