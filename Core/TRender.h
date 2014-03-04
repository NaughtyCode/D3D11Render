#ifndef TRENDER_H
#define TRENDER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TD3DDevice.h"
#include "TRenderTarget.h"
#include "TViewPort.h"
#include "TResource.h"
#include "TRenderConfig.h"
#include "TCamera.h"


class TD3DDevice;
class TRenderTarget;
class TViewPort;
class TShader;
class TResource;
class TRenderConfig;



class TRender
{
public:
    TRender();
    ~TRender();
    int CreateRender(HWND hWnd);
    void RenderFrame();
    void Release();
    
private:
    TD3DDevice*     Device;
    TRenderTarget*  RenderTarget;
    TViewPort*      ViewPort;
    TResource*      Resource;
};









#endif
