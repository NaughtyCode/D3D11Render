#ifndef ISHADER_H
#define ISHADER_H

#if _MSC_VER > 1000
# pragma once
#endif

class IShader
{
public:
    IShader();
    virtual ~IShader();
    virtual void PostEffect()=0;
    virtual LPVOID GetShaderBufferPointer()=0;
    virtual SIZE_T GetShaderBufferSize()=0;
    virtual void Release()=0;
};

#endif