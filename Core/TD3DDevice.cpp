#include "stdafx.h"
#include "TD3DDevice.h"

TD3DDevice::TD3DDevice(HWND hWnd):
			WindowHandle(hWnd),
			IsFullScreen(FALSE),
			Device(0),
			SwapChain(0),
			DeviceContext(0),
			DXGIFactory(0)
{
	
}

TD3DDevice::~TD3DDevice()
{
	
}

int TD3DDevice::CreateDevice()
{
	BOOL SupportD3D11Features;
	CheckD3D11Supported(SupportD3D11Features);
	assert(SupportD3D11Features);
	
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
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = WindowHandle;
	
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	
	SwapChainDesc.Windowed = !IsFullScreen;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
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
		&DeviceContext);
	
	if (FAILED(hr))
	{
		return 0;
	}
	
	return 1;
}

int TD3DDevice::CreateFactory(IDXGIFactory** ppDXGIFactory)
{
	HRESULT hr;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)ppDXGIFactory);
	if (FAILED(hr))
	{
		return 0;
	}
	return 1;
}

BOOL TD3DDevice::TestD3D11Device(UINT AdapterIndex,IDXGIAdapter* Adapter,D3D_FEATURE_LEVEL& OutFeatureLevel)
{
	ID3D11Device* D3DDevice = NULL;
	ID3D11DeviceContext* D3DDeviceContext = NULL;
	UINT DeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
	
#if defined( DEBUG ) || defined( _DEBUG )
	DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	DXGI_ADAPTER_DESC Desc;
	Adapter->GetDesc(&Desc);
	
	D3D_FEATURE_LEVEL RequestedFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	
	if(SUCCEEDED(D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		DeviceFlags,
		RequestedFeatureLevels,
		ARRAYSIZE(RequestedFeatureLevels),
		D3D11_SDK_VERSION,
		&D3DDevice,
		&OutFeatureLevel,
		&D3DDeviceContext
		)))
	{
		DXGI_ADAPTER_DESC AdapterDesc;
		Adapter->GetDesc(&AdapterDesc);
		D3DDevice->Release();
		D3DDeviceContext->Release();
		return TRUE;
	}
	return FALSE;
}

BOOL TD3DDevice::CheckD3D11Supported(BOOL& SupportD3D11Features)
{
	IDXGIFactory* DXGIFactory;
	CreateFactory(&DXGIFactory);
	if(!DXGIFactory)
	{
		return FALSE;
	}
	
	UINT AdapterIndex = 0;
	IDXGIAdapter* TempAdapter=0;
	BOOL bHasD3D11Adapter = FALSE;
	D3D_FEATURE_LEVEL MaxFeatureLevel;
	
	while( (DXGIFactory->EnumAdapters(AdapterIndex,&TempAdapter) ) != DXGI_ERROR_NOT_FOUND)
	{
		if(TempAdapter)
		{
			MaxFeatureLevel = D3D_FEATURE_LEVEL_11_0;
			if(TestD3D11Device(AdapterIndex,TempAdapter,MaxFeatureLevel))
			{
				SupportD3D11Features = (MaxFeatureLevel == D3D_FEATURE_LEVEL_11_0);
				bHasD3D11Adapter = TRUE;
			}
		}
		AdapterIndex++;
	};
	return bHasD3D11Adapter;
}

ID3D11Device* TD3DDevice::GetDevice() const
{
	return Device;
}

IDXGISwapChain* TD3DDevice::GetSwapChain() const
{
	return SwapChain;
}

ID3D11DeviceContext* TD3DDevice::GetDeviceContext() const
{
	return DeviceContext;
}

IDXGIFactory* TD3DDevice::GetFactory() const
{
	return DXGIFactory;
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
	SAFE_RELEASE(DXGIFactory);
	SAFE_RELEASE(DeviceContext);
}
