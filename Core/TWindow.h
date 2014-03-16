#ifndef TWindow_H
#define TWindow_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "resource.h"
#include "TD3D11Render.h"
#include "TMouseObject.h"

class TD3D11Render;
class TMouseObject;


class TWindow
{
public:
    TWindow();
    ~TWindow();
    int  CreateD3DWindow(UINT x,UINT y,UINT width,UINT height);
    void SetWindowPos(INT X,INT Y);
    void SetWindowTitle(const TCHAR* Title);
    void SetWindowSize(UINT width,UINT height);
    void EnterLoop();
    void Release();

private:
    HWND          WindowHandle;
    UINT          Width;
    UINT          Height;
	TMouseObject* MouseObject;
};



#endif
