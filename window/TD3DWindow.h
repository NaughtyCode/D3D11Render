#pragma once

#include "resource.h"
#include "TRender.h"

class TRender;

class TD3DWindow
{
public:
    TD3DWindow();
    ~TD3DWindow();
    int  CreateD3DWindow(UINT x,UINT y,UINT width,UINT height);
    void SetWindowPos(INT X,INT Y);
    void SetWindowTitle(const TCHAR* Title);
    void SetWindowSize(UINT width,UINT height);
    void EnterLoop();
    
private:
    HWND      hWnd;
    UINT      Width;
    UINT      Height;
    TRender*  D3D11Render;
};
