#ifndef TD3D11RENDER_H
#define TD3D11RENDER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TDevice.h"
#include "TRenderTarget.h"
#include "TViewPort.h"
#include "TResource.h"
#include "TCamera.h"


class TDevice;
class TRenderTarget;
class TViewPort;
class TShader;
class TResource;
class TD3D11RenderConfig;



class TD3D11Render
{
public:
    TD3D11Render();
    ~TD3D11Render();
    int CreateRender(HWND hWnd);
    
    void StartFrame();
    void EndFrame();
    
    void Release();
    
private:
    TRenderTarget*       RenderTarget;
    TViewPort*           CurrentViewPort;
    TViewPortArray       ViewPortArray;
    
    //state objects
    D3D11_DEPTH_STENCIL_DESC CurrentDepthState;
    D3D11_DEPTH_STENCIL_DESC CurrentStencilState;
    D3D11_RASTERIZER_DESC    CurrentRasterizerState;
    D3D11_BLEND_DESC         CurrentBlendState;
    
    //shader constant buffers
    TConstantBufferArray VSConstantBuffers;
    TConstantBufferArray HSConstantBuffers;
    TConstantBufferArray DSConstantBuffers;
    TConstantBufferArray PSConstantBuffers;
    TConstantBufferArray GSConstantBuffers;
    TConstantBufferArray CSConstantBuffers;
    
};

#endif
