#ifndef D3DDEVICE_H
#define D3DDEVICE_H

#if _MSC_VER > 1000
# pragma once
#endif



#include"stdafx.h"


class TD3DDevice
{
public:
    TD3DDevice(HWND hWnd);
    virtual ~TD3DDevice();
    int CreateDevice();
    int CreateFactory(IDXGIFactory** ppDXGIFactory);
    BOOL CheckD3D11Supported(BOOL& SupportD3D11Features);
    BOOL TestD3D11Device(UINT AdapterIndex,IDXGIAdapter* Adapter,D3D_FEATURE_LEVEL& OutFeatureLevel);
    
    IDXGIFactory* GetFactory() const;
    ID3D11Device* GetDevice() const;
    IDXGISwapChain* GetSwapChain() const;
    ID3D11DeviceContext* GetDeviceContext() const;
    
    HWND GetWindowHandle();
    void Present(); 
    void Release();
    
private:
    HWND                 WindowHandle;
    BOOL                 IsFullScreen;
    ID3D11Device*        Device;
    IDXGISwapChain*      SwapChain;
    ID3D11DeviceContext* DeviceContext;
    IDXGIFactory*        DXGIFactory;
    D3D_FEATURE_LEVEL    SelectedFeature;
    UINT                 MSAACount;
    UINT                 MSAAQuality;
    
    
};






#endif
