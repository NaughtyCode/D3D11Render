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
    ID3D11Device* GetDevice();
    IDXGISwapChain* GetSwapChain();
    ID3D11DeviceContext* GetDeviceContext();
    HWND GetWindowHandle();
    void Present(); 
    void Release();

private:
    HWND                 WindowHandle;
    BOOL                 IsFullScreen;
    ID3D11Device*        Device;
    IDXGISwapChain*      SwapChain;
    ID3D11DeviceContext* DeviceContext;
    D3D_FEATURE_LEVEL    SelectedFeature;
};






#endif
