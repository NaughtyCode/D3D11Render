#ifndef TBUFFER_H
#define TBUFFER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "IShader.h"

class IShader;
class TD3DDevice;
class TShader;
class TEffectShader;


class TBuffer
{
public:
    TBuffer(TD3DDevice* device);
    ~TBuffer();
    int CreateStaticVertexBuffer(void* pData,UINT size,UINT elemsize);
    int CreateVertexBuffer(void* pData,UINT size,UINT vertexsize,bool dynamic,bool streamout);
    int CreateIndexBuffer(void* pData,UINT size,UINT indexsize,bool dynamic);
    void PostResource();
    void Release();
    
private:
    TD3DDevice*        Device;
    ID3D11Buffer*      VertexBuffer;
    ID3D11Buffer*      IndexBuffer;
    UINT               VertexBufferSize;
    UINT               IndexBufferSize;
    UINT               VertexSize;
    BOOL               IsIndexDraw;
};

class TConstantBuffer
{
public:
    TConstantBuffer(TD3DDevice* device,WORD Size);
    ~TConstantBuffer();
    int  CreateConstantBuffer();
    void UpdateBuffer(const BYTE* Data, WORD Offset, WORD Size);
    BOOL PostConstantBuffer(BOOL IsDiscard);
    ID3D11Buffer* GetConstantBuffer();
    void Release();
    
private:
    BYTE*              Data;
    TD3DDevice*        Device;
    BOOL               NeedPost;
    UINT               CurrentSize;
    UINT               BufferSize;
    ID3D11Buffer*      ConstantBuffer;
};

#endif


