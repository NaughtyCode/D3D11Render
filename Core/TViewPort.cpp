#include "stdafx.h"
#include "Core.h"
#include "TViewPort.h"


TViewPort::TViewPort() :
		WindowHandle(GDevice->GetWindowHandle()),
		IsFullscreen(FALSE)
{
	
}

TViewPort::~TViewPort()
{
	
}

int TViewPort::CreateViewPort()
{
	RECT rect;
	GetWindowRect(WindowHandle, &rect);
	Width=rect.right - rect.left;
	Height=rect.bottom - rect.top;
	ZeroMemory(&ViewPort,sizeof(ViewPort));;
	ViewPort.Width = (FLOAT)Width;
	ViewPort.Height = (FLOAT)Height;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	GDevice->GetDeviceContext()->RSSetViewports(1,&ViewPort);
	return 1;
}

void TViewPort::ResizeViewPort(UINT width,UINT height,BOOL IsFullscreen)
{
	if(width != this->Width || height != this->Height)
	{
		this->Width  = width;
		this->Height = height;
		GDevice->GetSwapChain()->ResizeBuffers(1,
				this->Width,
				this->Height,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	}
	
	if(this->IsFullscreen != IsFullscreen)
	{
		this->IsFullscreen = IsFullscreen;
	}
}

UINT TViewPort::GetWidth() const
{
    return Width;
}

UINT TViewPort::GetHeight() const
{
    return Height;
}

void TViewPort::Release()
{

}
