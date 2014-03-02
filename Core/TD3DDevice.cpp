#include "stdafx.h"
#include "TD3DDevice.h"

TD3DDevice::TD3DDevice(HWND hWnd) :Handle(hWnd),
			Device(0),
			SwapChain(0),
			ImmediateContext(0)
{
}

TD3DDevice::~TD3DDevice()
{

}

int TD3DDevice::CreateDevice()
{
	HRESULT hr;
	RECT rect;
	UINT width = 900;
	UINT height = 600;
	GetWindowRect(Handle, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Handle;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D_FEATURE_LEVEL  FeatureArray[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		/*
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
		*/
	};

	UINT FeatureNum = ARRAYSIZE(FeatureArray);
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		FeatureArray,
		FeatureNum,
		D3D11_SDK_VERSION,
		&sd,
		&SwapChain,
		&Device,
		&SelectedFeature,
		&ImmediateContext);

	if (FAILED(hr))
	{
		return 0;
	}

	return 1;
}

ID3D11Device* TD3DDevice::GetDevice()
{
	return Device;
}

IDXGISwapChain* TD3DDevice::GetSwapChain()
{
	return SwapChain;
}

ID3D11DeviceContext* TD3DDevice::GetImmediateContext()
{
	return ImmediateContext;
}

HWND TD3DDevice::GetWindowHandle()
{
	return Handle;
}

void TD3DDevice::Release()
{
	SAFE_RELEASE(Device);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(ImmediateContext);
}
