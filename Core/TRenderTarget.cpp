#include "stdafx.h"
#include "TRenderTarget.h"


TRenderTarget::TRenderTarget(TD3DDevice* device) :
							Device(device),
							RenderTargetView(0),
							DepthStencil(0),
							DepthStencilView(0)

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
	SAFE_RELEASE(pBackBuffer);
	Device->GetImmediateContext()->OMSetRenderTargets(1,&RenderTargetView, NULL);
	if (!CreateDepthStencil())
	{
		assert(0);
		return 0;
	}
	return 1;
}

int TRenderTarget::CreateDepthStencil()
{
	RECT rect;
	HWND hWnd=Device->GetWindowHandle();
	UINT width;
	UINT height;
	GetWindowRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	HRESULT hr;
	D3D11_TEXTURE2D_DESC DescDepth;
	ZeroMemory( &DescDepth, sizeof(DescDepth) );
	DescDepth.Width = width;
	DescDepth.Height = height;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	hr = Device->GetDevice()->CreateTexture2D( &DescDepth, NULL, &DepthStencil );
	if( FAILED( hr ) )
	{
		return 0;
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC DescDSV;
	ZeroMemory( &DescDSV, sizeof(DescDSV) );
	DescDSV.Format = DescDepth.Format;
	DescDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DescDSV.Texture2D.MipSlice = 0;
	hr = Device->GetDevice()->CreateDepthStencilView( DepthStencil, &DescDSV, &DepthStencilView);
	if( FAILED( hr ) )
	{
		return 0;
	}
	Device->GetImmediateContext()->OMSetRenderTargets(1,&RenderTargetView,DepthStencilView);
	return 1;
}

void TRenderTarget::Clear()
{
	float ClearColor[4] = { 0.3f, 0.3f, 0.4f, 1.0f };
	Device->GetImmediateContext()->ClearRenderTargetView(RenderTargetView, ClearColor);
	Device->GetImmediateContext()->ClearDepthStencilView(DepthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);
}

ID3D11RenderTargetView* TRenderTarget::GetRenderTargetView()
{
	return RenderTargetView;
}

void TRenderTarget::Release()
{
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(DepthStencil);
	SAFE_RELEASE(DepthStencilView);
}

