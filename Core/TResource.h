#ifndef TRESOURCE_H
#define TRESOURCE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TShader.h"
#include "TBuffer.h"
#include "TD3DDevice.h"
#include "TEffectShader.h"
#include "TTexture.h"


class TD3DDevice;
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
    TResource(TD3DDevice* device);
    ~TResource();
    int CreateResource(const TCHAR* vsfile,const TCHAR* psfile);
    void CreateResource(const TCHAR* resourcefile);
    void CreateResource(const char* resourcefile);
    int CreateResource();
    void PostResource();
    void Release();
    
private:
    TD3DDevice*     Device;
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


