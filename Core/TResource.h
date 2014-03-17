#ifndef TRESOURCE_H
#define TRESOURCE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "Core.h"
#include "TDevice.h"
#include "GlobalMath.h"
#include "Definitions.h"

class TRenderContents;
class TViewPort;
class TD3D11RenderResource;
class TDevice;
class TShader;
class TBuffer;
class TEffectShader;
class TTexture;
class TConstantBuffer;
class TD3D11RenderParameterTransmitter;


typedef std::vector< TConstantBuffer* > TConstantBufferArray;
typedef std::vector< TShader* > TShaderArray;
typedef std::vector< TBuffer* > TBufferArray;
typedef std::vector< TEffectShader* > TEffectArray;
typedef std::vector< TTexture* > TTextureArray;
typedef std::vector< TViewPort* > TViewPortArray;


class TD3D11RenderParameterTransmitter
{
public:
    TD3D11RenderParameterTransmitter()
    {}
    
    virtual ~TD3D11RenderParameterTransmitter()
    {}
};

class TD3D11RenderResource
{
public:
    TD3D11RenderResource()
    {
        
    }
    
    virtual ~TD3D11RenderResource()
    {
        
    }
    
    virtual void InitRenderResource()
    {
        
    }
    
    virtual void DestroyRenderResource()
    {
        
    }
    
};


class TRenderContents
{
public:
    TRenderContents(){}
    virtual ~TRenderContents(){}
    
    char TextureFile[256];
    char VertexShaderFile[256];
    char VertexShaderEntry[64];
    char VertexShaderShaderModel[32];
    char PixelShaderFile[256];
    char PixelShaderEntry[64];
    char PixelShaderShaderModel[32];
    
    BOOL LoadResource(const char* Resource);
    
    BOOL ReadData(const char* SectionName,
            const char* ItemName,
            char* Data);
    
    BOOL ItemCheck(const char* SectionName,
            const char* CheckSectionName,
            const char* ItemName,
            const char* CheckItemName);
    
    void CopyItem(void* Dst,void* Src,int Size);
    
    void DumpContentsInfo();
};




class TTexture:public TD3D11RenderResource
{
public:
    TTexture();
    virtual ~TTexture(void);
    int CreateTexture(const char* TextureFileName);
    int CreateSampler();
    void PostTexture();
    void Release();
    
private:
    ID3D11SamplerState*       Sampler;
    ID3D11ShaderResourceView* TextureView;
    ID3D11Device*             Device;
    ID3D11DeviceContext*      DeviceContext;
};

class TBuffer:public TD3D11RenderResource
{
public:
    TBuffer();
    ~TBuffer();
    int CreateStaticVertexBuffer(void* pData,UINT size,UINT elemsize);
    int CreateVertexBuffer(void* pData,UINT size,UINT vertexsize,bool dynamic,bool streamout);
    int CreateIndexBuffer(void* pData,UINT size,UINT indexsize,bool dynamic);
    void PostResource();
    void Release();
    
private:
    ID3D11Buffer*      VertexBuffer;
    ID3D11Buffer*      IndexBuffer;
    UINT               VertexBufferSize;
    UINT               IndexBufferSize;
    UINT               VertexSize;
    BOOL               IsIndexDraw;
};

struct TConstantBufferContents
{
    TMatrix WorldViewProjectMatrix;
};

class TConstantBuffer:public TD3D11RenderResource
{
public:
    TConstantBuffer(UINT Size = 0,UINT NumBuffers = 1);
    ~TConstantBuffer();
    void CreateConstantBuffer();
    void UpdateBufferData(LPVOID pData, WORD Offset, WORD Size);
    BOOL UpdateConstantBufferResource(BOOL isDiscard);
    void PostConstantBuffer(UINT StartSlot,UINT NumBuffers);
    
    ID3D11Buffer* GetConstantBuffer();
    
    void Release();
    
private:
    LPID3D11Buffer* ConstantBuffers;
    UINT            MaxSize;
    BOOL            HasData;
    BYTE*           Data;
    UINT            CurrentSubBuffer;
    UINT            NumSubBuffers;
    UINT            CurrentUpdateSize;
    UINT            TotalUpdateSize;
};

class TShader:public TD3D11RenderResource
{
public:
    TShader();
    ~TShader();
    int CompileShaderFromFile(const char* filename,
                            LPCSTR entry,
                            LPCSTR shadermodel,
                            ID3DBlob** ppBlobOut);
    
    int CreateVertexShader(const char* filename,
                           const char* entry,
                           const char* shadermodel);
    
    int CreatePixelShader(const char* filename,
                          const char* entry,
                          const char* shadermodel);
    
    int InitConstantBuffer();
    
    int CreateConstantBuffer();
    
    virtual void PostEffect();
    
    virtual void Release();
    
    int CreateInputLayout();
    void SetLayoutType(INPUTTYPE_TYPE type);
    
private:
    ID3D11HullShader*       HullShader;
    ID3D11DomainShader*     DomainShader;
    ID3D11GeometryShader*   GeometryShader;
    ID3D11InputLayout*      InputLayout;
    ID3D11VertexShader*     VertexShader;
    ID3D11PixelShader*      PixelShader;
    ID3DBlob*               VertexShaderBuffer;
    ID3DBlob*               PixelShaderBuffer;
    TConstantBuffer*        ShaderResource;
    ID3D11DeviceContext*    DeviceContext;
    INPUTTYPE_TYPE          LayoutType;
};

class TIndexBuffer:public TD3D11RenderResource
{
public:
    ID3D11Buffer* Buffer;
    UINT Stride;
    UINT Usage;
    
    TIndexBuffer():Buffer(0),Stride(0),Usage(0)
    {
        
    }
    
    TIndexBuffer(ID3D11Buffer* buffer,
                UINT stride,
                UINT usage):
                Buffer(buffer),
                Stride(stride),
                Usage(usage)
    {
        
    }
    
    void InitRenderResource()
    {
        
    }
    
    void DestroyRenderResource()
    {
        SAFE_RELEASE(Buffer);
    }
    
    void CreateIndexBuffer(void* pData,UINT Size,UINT Pitch,bool IsDynamic);
    
};

class TVertexBuffer:public TD3D11RenderResource
{
public:
    ID3D11Buffer* Buffer;
    UINT Usage;
    
    TVertexBuffer():Buffer(0),Usage(0)
    {
        
    }
    
    TVertexBuffer(ID3D11Buffer* buffer,
                UINT usage):
                Buffer(buffer),
                Usage(usage)
    {
        
    }
    
    void InitRenderResource()
    {
        
    }
    
    void DestroyRenderResource()
    {
        SAFE_RELEASE(Buffer);
    }
    
    void CreateVertexBuffer( void* pData,UINT Size,UINT Pitch,bool IsDynamic,bool IsStreamOut);
};

class TBlendState : public TD3D11RenderResource
{
public:
    D3D11_BLEND_DESC BlendDesc;
    TBlendState(){}
    ~TBlendState(){}
};

class TSamplerState : public TD3D11RenderResource
{
public:
    D3D11_SAMPLER_DESC SamplerDesc;
};

class TRasterizerState : public TD3D11RenderResource
{
public:
    D3D11_RASTERIZER_DESC RasterizerDesc;
};

class TDepthState : public TD3D11RenderResource
{
public:
    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
};

class TStencilState : public TD3D11RenderResource
{
public:
    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    UINT StencilRef;
};

class TResource : public TD3D11RenderResource
{
public:
    TResource();
    ~TResource();
    void CreateResource(const TCHAR* resourcefile);
    void CreateResource(const char* resourcefile);
    int  CreateResource();
    void PostResource();
    void Release();
    
private:
    TShader*        Shader;
    TBuffer*        Buffer;
    TEffectShader*  EffectShader;
    TTexture*       Texture;
    TRenderContents RenderContent;
};

#endif


