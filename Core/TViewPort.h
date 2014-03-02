#pragma once
#include "TD3DDevice.h"

class TD3DDevice;

class TViewPort
{
public:
    TViewPort(TD3DDevice* device);
    ~TViewPort();
    int CreateViewPort();
    UINT GetWidth() const;
    UINT GetHeight() const;
    void ResizeViewPort(UINT width,UINT height,BOOL IsFullscreen);    
    void Release();
    
private:
    TD3DDevice*     Device;
    HWND            WindowHandle;
    UINT            Width;
    UINT            Height;
    BOOL            IsFullscreen;
    D3D11_VIEWPORT  ViewPort;
};




