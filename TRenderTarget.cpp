#include "stdafx.h"
#include "TRenderTarget.h"


TRenderTarget::TRenderTarget(TD3DDevice* device) :Device(device)
{
}

TRenderTarget::~TRenderTarget()
{
}

int TRenderTarget::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(Device->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D),(LPVOID*)&pBackBuffer))){
		return 0;
	}
	if (FAILED(Device->GetDevice()->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView))){
		return 0;
	}
	pBackBuffer->Release();
	Device->GetImmediateContext()->OMSetRenderTargets(1,&RenderTargetView, NULL);
	return 1;
}

void TRenderTarget::Clear()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	Device->GetImmediateContext()->ClearRenderTargetView(RenderTargetView, ClearColor);
	Device->GetSwapChain()->Present(0, 0);
}

ID3D11RenderTargetView* TRenderTarget::GetRenderTargetView()
{
	return RenderTargetView;
}


void TRenderTarget::Release()
{

}
