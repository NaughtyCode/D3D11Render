#include "stdafx.h"
#include "TD3DDevice.h"

TD3DDevice::TD3DDevice(HWND hWnd):
			WindowHandle(hWnd),
			IsFullScreen(FALSE),
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
	UINT width,height;
	GetWindowRect(WindowHandle,&rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = width;
	SwapChainDesc.BufferDesc.Height = height;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = !IsFullScreen;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;
	
	D3D_FEATURE_LEVEL  FeatureArray[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	
	UINT FeatureNum = ARRAYSIZE(FeatureArray);
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		FeatureArray,
		FeatureNum,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
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

ID3D11DeviceContext* TD3DDevice::GetDeviceContext()
{
	return ImmediateContext;
}

HWND TD3DDevice::GetWindowHandle()
{
	return WindowHandle;
}

void TD3DDevice::Present()
{
	SwapChain->Present(0,0);
}

void TD3DDevice::Release()
{
	SAFE_RELEASE(Device);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(ImmediateContext);
}
