#include "stdafx.h"
#include "TRenderTarget.h"


TRenderTarget::TRenderTarget(TD3DDevice* device) :
			Device(device),
			Resource(0),
			RenderTargetView(0),
			DepthStencilView(0),
			ReadDepthStencilView(0),
			ShaderResourceView(0),
			UnorderedAccessView(0),
			ClearColor(0.3f, 0.3f, 0.4f, 1.0f)

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
	HWND hWnd=Device->GetWindowHandle();
	UINT width;
	UINT height;
	RECT rect;
	GetWindowRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	
	HRESULT hr;
	D3D11_TEXTURE2D_DESC DepthDesc;
	ZeroMemory( &DepthDesc, sizeof(DepthDesc) );
	DepthDesc.Width = width;
	DepthDesc.Height = height;
	DepthDesc.MipLevels = 1;
	DepthDesc.ArraySize = 1;
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.CPUAccessFlags = 0;
	DepthDesc.MiscFlags = 0;
	hr = Device->GetDevice()->CreateTexture2D( &DepthDesc, NULL, &Resource);
	if( FAILED( hr ) )
	{
		return 0;
	}
	
	D3D11_DEPTH_STENCIL_VIEW_DESC StencilDesc;
	ZeroMemory( &StencilDesc, sizeof(StencilDesc) );
	StencilDesc.Format = DepthDesc.Format;
	StencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	StencilDesc.Texture2D.MipSlice = 0;
	hr = Device->GetDevice()->CreateDepthStencilView(Resource,&StencilDesc, &DepthStencilView);
	if( FAILED( hr ) )
	{
		return 0;
	}
	
	Device->GetImmediateContext()->OMSetRenderTargets(1,&RenderTargetView,DepthStencilView);
	return 1;
}

void TRenderTarget::Clear()
{
	Device->GetImmediateContext()->ClearRenderTargetView(RenderTargetView,(FLOAT*)&ClearColor);
	Device->GetImmediateContext()->ClearDepthStencilView(DepthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);
}

ID3D11RenderTargetView* TRenderTarget::GetRenderTargetView()
{
	return RenderTargetView;
}

void TRenderTarget::Release()
{
	SAFE_RELEASE(Resource);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(ReadDepthStencilView);
	SAFE_RELEASE(ShaderResourceView);
	SAFE_RELEASE(UnorderedAccessView);
}

