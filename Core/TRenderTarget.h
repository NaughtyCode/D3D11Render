#pragma once

#include "TD3DDevice.h"

class TD3DDevice;

class TRenderTarget
{
public:
    TRenderTarget(TD3DDevice* device);
    virtual ~TRenderTarget();
    int CreateRenderTarget();
    int CreateDepthStencil();
    ID3D11RenderTargetView* GetRenderTargetView();
    void Clear();
    void Release();
private:
    TD3DDevice*                Device;
    ID3D11Texture2D*           Resource;
    ID3D11RenderTargetView*    RenderTargetView;
    ID3D11DepthStencilView*    DepthStencilView;
    ID3D11DepthStencilView*    ReadDepthStencilView;
    ID3D11ShaderResourceView*  ShaderResourceView;
    ID3D11UnorderedAccessView* UnorderedAccessView;
    TColorF                    ClearColor;
};


