#ifndef TEFFECTSHADER_H
#define TEFFECTSHADER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "IShader.h"
#include "TD3DDevice.h"

class IShader;
class TD3DDevice;

class TEffectShader:public IShader
{
public:
    TEffectShader();
    virtual ~TEffectShader(void);
    int CompileShaderFromFile(const TCHAR* szFileName,LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
    int CreateEffectShader(const TCHAR* szFileName);
    virtual void PostEffect();
    virtual LPVOID GetShaderBufferPointer();
    virtual SIZE_T GetShaderBufferSize();
    virtual void Release();

private:
    ID3DX11Effect*          Effect;
    ID3DX11EffectTechnique* Technique;
    ID3DBlob*               EffectBuffer;
};



#endif
