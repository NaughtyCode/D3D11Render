#ifndef TRESOURCE_H
#define TRESOURCE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "Core.h"
#include "TDevice.h"
#include "GlobalMath.h"
#include "Definitions.h"

class IShader;
class TDevice;
class TShader;
class TBuffer;
class TEffectShader;
class TTexture;

typedef std::vector< TShader* >       ShaderArrayType;
typedef std::vector< TBuffer* >       BufferArrayType;
typedef std::vector< TEffectShader* > EffectArrayType;
typedef std::vector< TTexture* >      TextureArrayType;

class IShader
{
public:
    IShader(){}
    virtual ~IShader(){}
    virtual void PostEffect()=0;
    virtual void Release()=0;
};

class TResource
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
    
    ShaderArrayType   Shaders;
    BufferArrayType   Buffers;
    EffectArrayType   EffectShaders;
    TextureArrayType  Textures;
};

class TTexture
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

class TBuffer
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

class TConstantBuffer
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


class TShader:public IShader
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
    
    virtual void   PostEffect();
    
    virtual void   Release();
    
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

#endif


