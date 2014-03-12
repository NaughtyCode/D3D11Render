#ifndef TBUFFER_H
#define TBUFFER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TDevice.h"
#include "TShader.h"

class IShader;
class TDevice;
class TShader;
class TEffectShader;

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


#endif


