#ifndef TRENDERTARGET_H
#define TRENDERTARGET_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TD3DDevice.h"

class TD3DDevice;

class TRenderTarget
{
public:
    TRenderTarget();
    virtual ~TRenderTarget();
    int CreateRenderTarget();
    int CreateDepthStencil();
    ID3D11RenderTargetView* GetRenderTargetView();
    void Clear();
    void Release();
    
private:
    ID3D11Texture2D*           Resource;
    ID3D11RenderTargetView*    RenderTargetView;
    ID3D11DepthStencilView*    DepthStencilView;
    ID3D11DepthStencilView*    ReadDepthStencilView;
    ID3D11ShaderResourceView*  ShaderResourceView;
    ID3D11UnorderedAccessView* UnorderedAccessView;
    TColorF                    ClearColor;
};


#endif



