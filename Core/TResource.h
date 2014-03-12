#ifndef TRESOURCE_H
#define TRESOURCE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TShader.h"
#include "TBuffer.h"
#include "TDevice.h"
#include "TTexture.h"


class TDevice;
class TShader;
class TBuffer;
class TEffectShader;
class TTexture;

typedef std::vector< TShader* >       ShaderArrayType;
typedef std::vector< TBuffer* >       BufferArrayType;
typedef std::vector< TEffectShader* > EffectArrayType;
typedef std::vector< TTexture* >      TextureArrayType;

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

#endif


